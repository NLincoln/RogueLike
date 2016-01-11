#pragma once
#include "Item.h"
#include <vector>
#include "Entity.h"
#include "CollisionSystem.h"
#include "Component.h"

class CollisionSystem;
class EnemyManager;
class EventManager;

struct EnemyDescription : EntityDescription
{
	uint BaseExperience;
};

class Enemy : public Entity
{
	std::vector<Item> m_Inventory;
	CollisionCallback m_CollisionCallback;

	EventManager* m_EventManagerRef;


	int m_Health;

public:
	void ReceiveDamage(int Damage);

	Enemy(CollisionSystem& CollisionSystem, EnemyManager& EnemyManager, EventManager* EventHandler);

	~Enemy();
};

