#pragma once

#include "Entity.h"
#include "Event.h"
#include "CollisionSystem.h"

class MovementSystem;
class EventManager;

class Player : public Entity
{
	CollisionCallback m_CollisionCallback;

public:
	Player(SpriteBlock sprite, MovementSystem& manager, CollisionSystem& CollisionSystem);
	~Player();
};

