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
#include "EntityManager.h"


int main(int argc, const char** argv)
{
	sf::RenderWindow* Window = new sf::RenderWindow();
	sf::VideoMode Mode;
	Mode.height = WINDOW_HEIGHT;
	Mode.width = WINDOW_WIDTH;
	SpriteFactory Factory("TileSet.png");
	Window->create(Mode, "First Window");
	
	EventManager EventManager;
	MovementSystem EntityManager(EventManager);

	RenderManager RenderManager;
	
	Cursor* c = new Cursor(Factory["X"], EntityManager);
	c->SetWorldPos(WorldPos(10, 3));
	RenderManager.AddEntity(c);


	Player* p = new Player(Factory["@"], EntityManager);
	p->SetWorldPos(WorldPos(5, 6));
	RenderManager.AddEntity(p);
	EntityManager.SetFocus(p);

	EventCallback Switch = [&] (EventType Type)
	{
		switch(Type)
		{
		case EventType::NUMPAD_1:
			EntityManager.SetFocus(c);
			break;
		case EventType::NUMPAD_2:
			EntityManager.SetFocus(p);
			break;
		default: break;
		}
	};

	EventManager.AddHook(ERange::NumKey, Switch);

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
