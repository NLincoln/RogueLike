#pragma once
#include "Item.h"
#include <vector>
#include "Entity.h"
#include "CollisionSystem.h"
#include "Component.h"

class RenderManager;
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
	int m_DeathHP;
public:
	bool isDead() const; 
	void ReceiveDamage(int Damage);

	Enemy(RenderManager& RenderManager, CollisionSystem& CollisionSystem, EnemyManager& EnemyManager, EventManager* EventHandler);

	~Enemy();
};

