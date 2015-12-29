#include "EntityManager.h"
#include "Event.h"


void EntityManager::SetFocus(Entity* NewFocus)
{
	m_FocusEntity = NewFocus;
}

void EntityManager::AddHook(const EventRange Range, EventCallback Callback, Entity* Entity)
{
	for (uint i = static_cast<uint>(Range.first); i <= static_cast<uint>(Range.second); ++i)
	{
		AddHook(static_cast<EventType>(i), Callback, Entity);
	}
}

void EntityManager::AddHook(const EventType Type, EventCallback Callback, Entity* Entity)
{
	m_EntityCallbacks[Entity][Type] = Callback;
}

void EntityManager::AddEntity(Entity* NewEntity)
{
	m_Entities.push_back(NewEntity);
}

EntityManager::EntityManager(EventManager& Manager)
{
	Manager.AddHook(ERange::Movement, [&] (EventType Type)
	{
		m_EntityCallbacks[m_FocusEntity][Type](Type);
	});
}


EntityManager::~EntityManager()
{
}
