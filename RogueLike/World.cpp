#include "World.h"
#include "EntityCommon.h"
#include "RenderManager.h"
#include "Wall.h"
#include "SpriteFactory.h"
#include "CollisionSystem.h"
#include <stack>
#include <random>
#include "Tree.h"

template <typename T>
T GetRandom(T min, T max)
{
	return (static_cast<float>(rand()) / RAND_MAX) * (max - min) + min;
}

uint GetRandomUINT(uint min, uint max)
{
	std::random_device rd;
	std::mt19937 rng(rd());
	std::uniform_int_distribution<uint> uni(min, max);
	return uni(rng);
}


Entity* WorldGenerator::At(WorldPos Coords)
{
	return operator[](Coords);
}

void WorldGenerator::CreateRandom(RenderManager& RenderManager, CollisionSystem& CollisionSystem, SpriteFactory& SpriteFactory)
{
	struct desc
	{
		uint ROOM_TRIES;
		uint BOX_WIDTH;
		uint BOX_HEIGHT;
	};

	const desc desc = { 50, 9, 7 };

	for (uint i = 0; i < m_Dimensions.x * m_Dimensions.y; ++i)
		m_Entities.emplace_back();


	//The first step is to create a bunch of rooms

	std::vector<sf::Rect<int>> AllRooms;

	for (uint i = 0; i < desc.ROOM_TRIES; ++i)
	{
		sf::Rect<int> Box;
		Box.height = desc.BOX_HEIGHT;
		Box.width = desc.BOX_WIDTH;
		Box.top = GetRandom<uint>(0, (m_Dimensions.y - Box.height) / 2 - 1) * 2 + 1;
		Box.left = GetRandom<uint>(0, (m_Dimensions.x - Box.width) / 2 - 1) * 2 + 1;

		//We have to check all the other boxes and make sure ours won't intersect
		bool DoesInterset = false;
		for (auto Room : AllRooms)
		{
			auto TempBox = Box;
			TempBox.top--;
			TempBox.left--;
			TempBox.width += 2;
			TempBox.height += 2;

			if (Room.intersects(TempBox))
				DoesInterset = true;
		}
		if (!DoesInterset)
			AllRooms.push_back(Box);
	}

	for (uint x = 0; x < m_Dimensions.x; ++x)
	{
		for (uint y = 0; y < m_Dimensions.y; ++y)
		{
			bool IsEmpty = false;

			for(auto Room : AllRooms)
				if (Room.contains(x, y))
					IsEmpty = true;

			if (!IsEmpty)
			{
				Entity* wall = m_Entities[y * m_Dimensions.x + x];
				wall = new Wall(SpriteFactory["*"]);
				wall->SetWorldPos(WorldPos(x, y));
				m_Entities[y * m_Dimensions.x + x] = wall;
			}
		}
	}
	/*
	 * At this point, A bunch of rooms have been carved out of a field of walls
	 * Next, we start carving out tunnels for the player to wander through
	 */

	WorldPos StartPos = WorldPos(1, 1);
	while(!At(StartPos)) // Find a wall to start carving at. Most of the time, this step will be skipped
	{
		StartPos.x += 2; //Always, ALWAYS carve in increments of two.
		StartPos.y += 2;
	}

	//So the miner is now at a point where it has a wall to dig out.... Therefore, it's now time to start digging!

	auto deleteAt = [this] (WorldPos Coords)
	{
		if (At(Coords))
		{
			delete m_Entities[Coords.y * m_Dimensions.x + Coords.x];
			m_Entities[Coords.y * m_Dimensions.x + Coords.x] = nullptr;
		}
	};

	/*
	 * So, because of things that are going to happen farther down the road... We need to change this code just a teensy tiny 
	 * amount to return the maze that we have created in the form of a tree. A tree, by the way, I have wonderfully created.
	 */

	/* Because any problem can be solved with recursive lambda functions! */
	std::function<Node<WorldPos>*(WorldPos)> Carve = [&deleteAt, &Carve, this] (WorldPos MinerPos)
	{
		/*
		 * Delete the place we're currently at. Select a random direction, shift over there, and try to carve it out.
		 * If it comes back true, carve out the block in between, otherwise, do nothing.
		 * Randomly select another direction until all four directions have been selected. 
		 * return true, since this location was valid. 
		 */

		if (!At(MinerPos))
			return static_cast<Node<WorldPos>*>(nullptr);
		deleteAt(MinerPos);
		
		auto Shuffle = [] (std::vector<direction> list)
		{
			std::stack<direction> result;
			while(!list.empty())
			{
				uint selection = GetRandomUINT(0, list.size() - 1);
				result.push(list[selection]);
				list.erase(list.begin() + selection);
			}
			return result;
		};

		std::stack<direction> DirectionOrder = [&] ()
		{
			std::vector<direction> result;
			for (uint i = 0; i < 4; ++i)
				result.push_back(static_cast<direction>(i));

			return Shuffle(result);
		}();

		Node<WorldPos>* CurrentNode = new Node<WorldPos>();
		CurrentNode->SetData(MinerPos);

		while(!DirectionOrder.empty())
		{

			direction dir = DirectionOrder.top();
			DirectionOrder.pop();
			

			WorldPos NextPos = Move(MinerPos, dir, 2);
			Node<WorldPos>* NextNode = Carve(NextPos);

			if (NextNode)
			{
				WorldPos MiddlePos = Move(MinerPos, dir, 1);
				deleteAt(MiddlePos);
				CurrentNode->AddChild(NextNode);
			}
		}

		return CurrentNode;
	};

	Node<WorldPos>* RootNode = Carve(StartPos);

	/*
	 * At this point, we have rooms and tunnels carved out of the walls. 
	 * It is now time to connect some of the rooms to the hallways at certain locations. 
	 */

	for (auto Room : AllRooms)
	{
		auto TempRoom = Room;
		--TempRoom.top;
		--TempRoom.left;
		TempRoom.height += 2;
		TempRoom.width += 2;

		std::vector<WorldPos> Walls;
		
		uint x = TempRoom.left + 2;
		uint y = TempRoom.top;

		//Add the top row
		for (x = TempRoom.left + 1; x <= TempRoom.left + TempRoom.width; x += 2)
			Walls.push_back(WorldPos(x, y));
	
		y = TempRoom.top + TempRoom.height - 1;

		//Add the bottom row
		for (x = TempRoom.left + 1; x <= TempRoom.left + TempRoom.width; x += 2)
			Walls.push_back(WorldPos(x, y));

		x = TempRoom.left;
		
		//Add the left side
		for (y = TempRoom.top + 1; y <= TempRoom.top + TempRoom.height; y += 2)
			Walls.push_back(WorldPos(x, y));

		x = TempRoom.left + TempRoom.width - 1;

		//Add the right side
		for (y = TempRoom.top + 1; y <= TempRoom.top + TempRoom.height; y += 2)
			Walls.push_back(WorldPos(x, y));



		Walls = [](std::vector<WorldPos> list) // Fisher-Yates shuffling algo
		{
			std::vector<WorldPos> result;
			while (!list.empty())
			{
				uint selection = GetRandomUINT(0, list.size() - 1);
				result.push_back(list[selection]);
				list.erase(list.begin() + selection);
			}
			return result;
		}(Walls);

		uint NumToDelete = GetRandomUINT(1, 3);

		for (uint i = 0; i < NumToDelete; ++i)
			deleteAt(Walls[i]);

	}

	/* 
	* Finally, we have an area that is carved out. Rooms are open to the hallways. Everything is going well.
	* It is at this point that We begin finding empty areas that are surrounded by 3 (or more...) walls. Close these,
	* Until none remain.
	*/

	uint NumFilled = 1; // Because it doesn't *really* matter how many we fill in, we start this off at 1.

	auto Fill = [&SpriteFactory, this] (WorldPos Pos)
	{
		Entity* wall = m_Entities[Pos.y * m_Dimensions.x + Pos.x];
		wall = new Wall(SpriteFactory["*"]);
		wall->SetWorldPos(WorldPos(Pos.x, Pos.y));
		m_Entities[Pos.y * m_Dimensions.x + Pos.x] = wall;
	};

	for (uint x = 0; x < m_Dimensions.x; ++x)
	{
		for (uint y = 0; y < m_Dimensions.y; ++y)
		{
			if(At(WorldPos(x, y)))
			{
				RenderManager.AddEntity(At(WorldPos(x, y)));
				CollisionSystem.AddEntity(At(WorldPos(x, y)));
			}
		}
	}
}

Entity* WorldGenerator::operator[](WorldPos Coords)
{
	if(Coords.x < m_Dimensions.x && Coords.y < m_Dimensions.y)
		return m_Entities[Coords.y * m_Dimensions.x + Coords.x];
	else return nullptr;
}

WorldGenerator::WorldGenerator(sf::Vector2u Dimensions = sf::Vector2u(WINDOW_WIDTH + 1, WINDOW_HEIGHT + 1)) : m_Dimensions(Dimensions) { }

WorldGenerator::~WorldGenerator() { }
