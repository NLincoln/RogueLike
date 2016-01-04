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
	SpriteFactory Factory("TileSet.png");
	Window->create(Mode, "First Window");

	EventManager EventManager;
	MovementSystem MovementSystem(EventManager);
	CollisionSystem CollisionSystem;
	RenderManager RenderManager;

	World World(WorldPos(WINDOW_WIDTH / 16, WINDOW_HEIGHT / 16));

	World.CreateRandom(RenderManager, CollisionSystem, Factory);

	Player* p = new Player(Factory["@"], MovementSystem, CollisionSystem);

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


	EventCallback Close = [&] (EventType Type)
	{
		Window->close();
	};

	EventManager.AddHook(ERange::NumKey, Switch);
	EventManager.AddHook(EventType::EXIT_GAME, Close);

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
