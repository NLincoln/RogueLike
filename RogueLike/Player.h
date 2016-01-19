#pragma once

#include "Entity.h"
#include "Event.h"
#include "CollisionSystem.h"
#include "Component.h"
#include "Item.h"
#include "World.h"

class RenderManager;
class MovementSystem;
class EventManager;

class Player : public Entity
{
	std::vector<Item> m_Inventory;
	
	int m_Health;
	int m_DeathHP;

	WorldGenerator* m_WorldRef;

	CollisionCallback m_CollisionCallback;
	EventManager* m_EventManagerRef;

public:
	void ReceiveDamage(int Damage);
	std::vector<Entity*> FindLine(WorldPos Start, WorldPos End) const;
	std::function<void(EventType)> MovementCallback();

	Player(SpriteBlock sprite, 
		   RenderManager& RenderManager, 
		   MovementSystem& MovementSystem, 
		   CollisionSystem& CollisionSystem, 
		   EventManager* EventManager,
		   WorldGenerator* WorldGenerator);
	~Player();
};

