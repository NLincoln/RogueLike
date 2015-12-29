#include "EntityManager.h"
#include "Event.h"


void MovementSystem::SetFocus(Entity* NewFocus)
{
	m_FocusEntity = NewFocus;
}

void MovementSystem::AddHook(const EventRange Range, EventCallback Callback, Entity* Entity)
{
	for (uint i = static_cast<uint>(Range.first); i <= static_cast<uint>(Range.second); ++i)
	{
		AddHook(static_cast<EventType>(i), Callback, Entity);
	}
}

void MovementSystem::AddHook(const EventType Type, EventCallback Callback, Entity* Entity)
{
	m_EntityCallbacks[Entity][Type] = Callback;
}

void MovementSystem::AddEntity(Entity* NewEntity)
{
	m_Entities.push_back(NewEntity);
}

MovementSystem::MovementSystem(EventManager& Manager)
{
	Manager.AddHook(ERange::Movement, [&] (EventType Type)
	{
		m_EntityCallbacks[m_FocusEntity][Type](Type);
	});
}


MovementSystem::~MovementSystem()
{
}
