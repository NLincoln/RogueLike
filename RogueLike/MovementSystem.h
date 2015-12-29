#pragma once
#include "Entity.h"
#include "Event.h"

class EventManager;

class MovementSystem
{
	Entity* m_FocusEntity;
	std::map<Entity*, std::map<EventType, EventCallback>> m_EntityCallbacks;

	std::vector<Entity*> m_Entities;
	
public:
	void SetFocus(Entity* NewFocus);

	void AddHook(const EventRange Range, EventCallback Callback, Entity* Entity);
	void AddHook(const EventType  Type, EventCallback Callback, Entity* Entity);

	void AddEntity(Entity* NewEntity);

	MovementSystem(EventManager& Manager);

	~MovementSystem();
};

