#pragma once

#include "Entity.h"
#include "Event.h"

class EventManager;

class Player : public Entity
{
	//void MovementCallback(EventType Event);
public:
	Player(SpriteBlock sprite, EventManager& manager);
	~Player();
};

