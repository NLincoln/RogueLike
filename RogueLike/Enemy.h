#pragma once
#include "Item.h"
#include <vector>
#include "Entity.h"
#include "CollisionSystem.h"
#include "Component.h"
#include "World.h"

enum class EventType : uint;
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
	WorldGenerator* m_WorldRef;
	int m_MaxHP;
	int m_Health;
	int m_DeathHP;
public:
	std::function<void(EventType)> MovementCallback();

	bool isDead() const; 
	void ReceiveDamage(int Damage);

	Enemy(RenderManager& RenderManager, CollisionSystem& CollisionSystem, EnemyManager& EnemyManager, EventManager* EventManager, WorldGenerator* World);

	~Enemy();

	friend class RenderManager;
};

