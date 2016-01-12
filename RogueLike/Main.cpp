//
//
//
//
//

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "SpriteFactory.h"
#include "RenderCommon.h"
#include "RenderManager.h"
#include "Entity.h"
#include "Player.h"
#include "Event.h"
#include "MovementSystem.h"
#include "World.h"
#include "EnemyManager.h"

template <typename T>
T GetRandom(T min, T max)
{
	return (static_cast<float>(rand()) / RAND_MAX) * (max - min) + min;
}

int main(int argc, const char** argv)
{
	srand(time(nullptr));
	sf::RenderWindow* Window = new sf::RenderWindow();
	sf::VideoMode Mode;
	Mode.height = WINDOW_HEIGHT;
	Mode.width = WINDOW_WIDTH;
	SpriteFactory SpriteFactory("TileSet.png");
	Window->create(Mode, "RogueLike");

	EventManager EventManager;
	MovementSystem MovementSystem(EventManager);
	CollisionSystem CollisionSystem;
	RenderManager RenderManager;


	WorldGenerator World(WorldPos(WINDOW_WIDTH / 16 - 1, WINDOW_HEIGHT / 16 - 1));

	World.CreateRandom(RenderManager, CollisionSystem, SpriteFactory);

	Player* p = new Player(SpriteFactory["@"], MovementSystem, CollisionSystem);

	EnemyManager EnemyManager(EventManager, MovementSystem, p);
	Enemy* e = new Enemy(RenderManager, CollisionSystem, EnemyManager, &EventManager);
	e->SetSprite(SpriteFactory["E"]);
	e->SetWorldPos(WorldPos(1, 3));

	EventCallback Switch = [&] (EventType Type)
	{
		switch(Type)
		{
		case EventType::NUMPAD_2:
			p->SetWorldPos(WorldPos(1, 1));
			RenderManager.AddEntity(p);
			CollisionSystem.AddEntity(p);

			MovementSystem.SetFocus(p);
			break;
		default: break;
		}
	};

	EventCallback Kill = [&] (EventType Type)
	{
	};

	EventCallback Close = [&] (EventType Type)
	{
		Window->close();
	};

	EventManager.AddHook(ERange::NumKey, Switch);
	EventManager.AddHook(EventType::EXIT_GAME, Close);
	EventManager.AddHook(EventType::ENEMY_DEATH, Kill);

	RenderManager.SetRenderTarget(Window);
	while (Window->isOpen())
	{
		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;
		while (Window->pollEvent(event))
		{
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed)
				Window->close();
			EventManager.ProcessSFMLEvent(event);
		}
		Window->clear();
		RenderManager.Draw();
		Window->display();
	}
	return 0;
}
