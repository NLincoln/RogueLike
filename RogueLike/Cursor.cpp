#include "Cursor.h"

#include "Event.h"
#include "MovementSystem.h"
#include "EntityCommon.h"

Cursor::Cursor(const SpriteBlock sprite, MovementSystem& manager)
{
	m_Sprite = sprite;

	manager.AddHook(ERange::Movement, this, [&](EventType Event)
	{
		m_WorldPos = Move(m_WorldPos, Event, 1);
	});
}


Cursor::~Cursor()
{
}
