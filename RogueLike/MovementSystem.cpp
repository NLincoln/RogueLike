#include "Event.h"
#include "MovementSystem.h"


void MovementSystem::SetFocus(Entity* NewFocus)
{
	m_FocusEntity = NewFocus;
}

void MovementSystem::AddHook(const EventRange Range, Entity* Entity, EventCallback Callback)
{
	for (uint i = static_cast<uint>(Range.first); i <= static_cast<uint>(Range.second); ++i)
	{
		AddHook(static_cast<EventType>(i), Entity, Callback);
	}
}

void MovementSystem::AddHook(const EventType Type, Entity* Entity, EventCallback Callback)
{
	if (std::find(m_Entities.begin(), m_Entities.end(), Entity) == m_Entities.end())
		m_Entities.push_back(Entity);
	
	m_EntityCallbacks[Entity][Type].push_back(Callback);
}

void MovementSystem::AddEntity(Entity* NewEntity)
{
	m_Entities.push_back(NewEntity);
}

MovementSystem::MovementSystem(EventManager& Manager)
{
	Manager.AddHook(ERange::Movement, [&] (EventType Type)
	{
		for (auto Callback : m_EntityCallbacks[m_FocusEntity][Type])
			Callback(Type);
	});
}


MovementSystem::~MovementSystem()
{
}
