#pragma once

#include "Entity.h"
#include "Event.h"
#include "CollisionSystem.h"
#include "Component.h"
#include "Item.h"

class MovementSystem;
class EventManager;

class Player : public Entity
{
	std::vector<Item> m_Inventory;


	CollisionCallback m_CollisionCallback;


public:

	Player(SpriteBlock sprite, MovementSystem& manager, CollisionSystem& CollisionSystem);
	~Player();
};

