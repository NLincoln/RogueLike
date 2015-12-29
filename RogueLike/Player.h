#pragma once

#include "Entity.h"
#include "Event.h"

class EntityManager;
class EventManager;

class Player : public Entity
{
	//void MovementCallback(EventType Event);
public:
	Player(SpriteBlock sprite, EntityManager& manager);
	~Player();
};

