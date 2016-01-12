#pragma once
#include "Entity.h"
#include "Event.h"

class EventManager;

class MovementSystem
{
	Entity* m_FocusEntity;
	std::map<Entity*, std::map<EventType, std::vector<EventCallback>>> m_EntityCallbacks;

	std::vector<Entity*> m_Entities;
	
public:
	void SetFocus(Entity* NewFocus);

	void AddHook(const EventRange Range, Entity* Entity, EventCallback Callback);
	void AddHook(const EventType  Type, Entity* Entity, EventCallback Callback);

	void AddEntity(Entity* NewEntity);
	void RemoveEntity(Entity* Entity);

	MovementSystem(EventManager& Manager);

	~MovementSystem();
};

