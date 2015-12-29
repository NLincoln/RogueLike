#include "Player.h"
#include "Event.h"
#include "MovementSystem.h"
#include <functional>


Player::Player(const SpriteBlock sprite, MovementSystem& manager, CollisionSystem& CollisionSystem)
{
	m_Sprite = sprite;

	CollisionSystem.AddEntity(this);
	m_CollisionCallback = CollisionSystem.GetCallback();

	manager.AddHook(ERange::Movement, [&] (EventType Event)
	{
		WorldPos NewPos = m_WorldPos;
		switch (Event)
		{
		case EventType::MOVE_LEFT:
			NewPos.x--;
			break;
		case EventType::MOVE_RIGHT:
			NewPos.x++;
			break;
		case EventType::MOVE_UP:
			NewPos.y--;
			break;
		case EventType::MOVE_DOWN:
			NewPos.y++;
			break;
		default: break;
		}
		if (m_CollisionCallback(NewPos))
			m_WorldPos = NewPos;
			
	}, this);

}

Player::~Player()
{
}
