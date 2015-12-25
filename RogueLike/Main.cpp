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


int main(int argc, const char** argv)
{
	sf::RenderWindow Window;
	sf::VideoMode Mode;
	Mode.height = WINDOW_HEIGHT;
	Mode.width = WINDOW_WIDTH;
	SpriteFactory Factory("TileSet.png");
	Window.create(Mode, "First Window");
	
	EventManager EventManager;


	RenderManager Manager;
	
	Cursor* c = new Cursor(Factory["X"], EventManager);
	c->SetWorldPos(WorldPos(10, 3));
	Manager.AddEntity(c);


	Player* p = new Player(Factory["@"], EventManager);
	p->SetWorldPos(WorldPos(5, 6));
	Manager.AddEntity(p);
	

	Manager.SetRenderTarget(&Window);
	

	Window.clear(sf::Color::Black);

	while (Window.isOpen())
	{
		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;
		while (Window.pollEvent(event))
		{
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed)
				Window.close();
			EventManager.ProcessSFMLEvent(event);
		}
		Window.clear();
		Manager.Draw();
		Window.display();
	}
	return 0;
}
