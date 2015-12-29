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
#include "Cursor.h"
#include "MovementSystem.h"
#include "Wall.h"


int main(int argc, const char** argv)
{
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


	Player* p = new Player(Factory["@"], MovementSystem, CollisionSystem);
	p->SetWorldPos(WorldPos(5, 6));
	RenderManager.AddEntity(p);
	MovementSystem.SetFocus(p);

	Wall* w = new Wall(Factory[SPRITENAMES::DOOR]);
	w->SetWorldPos(WorldPos(10, 8));
	RenderManager.AddEntity(w);
	CollisionSystem.AddEntity(w);

	EventCallback Switch = [&] (EventType Type)
	{
		switch(Type)
		{
		case EventType::NUMPAD_2:
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
