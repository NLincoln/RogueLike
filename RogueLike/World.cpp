#include "World.h"
#include "RenderManager.h"
#include "Wall.h"
#include "SpriteFactory.h"
#include "CollisionSystem.h"
#include <stack>

template <typename T>
T GetRandom(T min, T max)
{
	return (static_cast<float>(rand()) / RAND_MAX) * (max - min) + min;
}


Entity* World::At(WorldPos Coords)
{
	return operator[](Coords);
}

void World::CreateRandom(RenderManager& RenderManager, CollisionSystem& CollisionSystem, SpriteFactory& SpriteFactory)
{
	struct desc
	{
		uint ROOM_TRIES;
		uint BOX_WIDTH;
		uint BOX_HEIGHT;
	};

	const desc desc = {100, 7, 5 };

	for (uint i = 0; i < m_Dimensions.x * m_Dimensions.y; ++i)
		m_Entities.emplace_back();


	//The first step is to create a bunch of rooms

	std::vector<sf::Rect<int>> AllRooms;

	for (uint i = 0; i < desc.ROOM_TRIES; ++i)
	{
		sf::Rect<int> Box;
		Box.height = desc.BOX_HEIGHT;
		Box.width = desc.BOX_WIDTH;
		Box.top = GetRandom<uint>(0, (m_Dimensions.y - Box.height) / 2) * 2 + 1;
		Box.left = GetRandom<uint>(0, (m_Dimensions.x - Box.width) / 2) * 2 + 1;

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

	WorldPos MinerPos = WorldPos(1, 1);
	while(!At(MinerPos)) // Find a wall to start carving at. Most of the time, this step will be skipped
	{
		MinerPos.x += 2; //Always, ALWAYS carve in increments of two.
		MinerPos.y += 2;
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

	/* Because any problem can be solved with recursive lambda functions! */
	std::function<bool(WorldPos)> Carve = [&deleteAt, &Carve, this] (WorldPos MinerPos)
	{
		/*
		 * Delete the place we're currently at. Select a random direction, shift over there, and try to carve it out.
		 * If it comes back true, carve out the block in between, otherwise, do nothing.
		 * Randomly select another direction until all four directions have been selected. 
		 * return true, since this location was valid. 
		 */

		if (!At(MinerPos))
			return false;
		deleteAt(MinerPos);
		enum class direction
		{
			North = 0, South, East, West
		};
		
		auto Shuffle = [] (std::vector<direction> list)
		{
			std::stack<direction> result;
			while(!list.empty())
			{
				uint selection = GetRandom<uint>(0, list.size());
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

		while(!DirectionOrder.empty())
		{

			direction dir = DirectionOrder.top();
			DirectionOrder.pop();
			
			auto Move = [] (WorldPos CurrentPos, direction dir, uint magnitude)
			{
				switch (dir)
				{
				case direction::North: CurrentPos.y -= magnitude; break;
				case direction::South: CurrentPos.y += magnitude; break;
				case direction::East:  CurrentPos.x += magnitude; break;
				case direction::West:  CurrentPos.x -= magnitude; break;
				default: break;
				}
				return CurrentPos;
			};

			WorldPos NextPos = Move(MinerPos, dir, 2);

			if(Carve(NextPos))
			{
				WorldPos MiddlePos = Move(MinerPos, dir, 1);
				deleteAt(MiddlePos);
			}
		}
		return true;
	};

	Carve(MinerPos);

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

Entity* World::operator[](WorldPos Coords)
{
	if(Coords.x <= m_Dimensions.x && Coords.y <= m_Dimensions.y)
		return m_Entities[Coords.y * m_Dimensions.x + Coords.x];
	else return nullptr;
}

World::World(sf::Vector2u Dimensions = sf::Vector2u(WINDOW_WIDTH + 1, WINDOW_HEIGHT + 1)) : m_Dimensions(Dimensions) { }

World::~World() { }
