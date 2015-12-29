#include "Cursor.h"

#include "Event.h"
#include "EntityManager.h"

Cursor::Cursor(const SpriteBlock sprite, EntityManager& manager)
{
	m_Sprite = sprite;

	

	manager.AddHook(ERange::Movement, [&](EventType Event)
	                {
		                switch (Event)
		                {
		                case EventType::MOVE_LEFT:
			                m_WorldPos.x--;
			                break;
		                case EventType::MOVE_RIGHT:
			                m_WorldPos.x++;
			                break;
		                case EventType::MOVE_UP:
			                m_WorldPos.y--;
			                break;
		                case EventType::MOVE_DOWN:
			                m_WorldPos.y++;
			                break;
		                default: break;
		                }
	                }, this);

}


Cursor::~Cursor()
{
}
