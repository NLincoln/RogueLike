#pragma once
#include "Item.h"
#include <vector>
#include "Entity.h"
#include "CollisionSystem.h"
#include "Component.h"
#include "World.h"
#include "EntityCommon.h"

enum class EventType : uint;
class RenderManager;
class CollisionSystem;
class EnemyManager;
class EventManager;

struct EnemyDescription : EntityDescription
{
	uint BaseExperience;
};

using AIFunction = std::function<void()>;

class Enemy : public Entity
{
	enum class StateType { Rest, Pursuit, LastKnown };

	std::vector<Item> m_Inventory;
	CollisionCallback m_CollisionCallback;

	StateType m_CurrentState;

	EnemyManager* m_EnemyManagerRef;
	EventManager* m_EventManagerRef;
	WorldGenerator* m_WorldRef;

	WorldPos m_PrevTarget;

	int m_MaxHP;
	int m_Health;
	int m_DeathHP;

public:
	std::function<void(EventType)> MovementCallback();

	bool isDead() const; 
	void ReceiveDamage(int Damage);

	Enemy(RenderManager& RenderManager, CollisionSystem& CollisionSystem, EnemyManager* EnemyManager, EventManager* EventManager, WorldGenerator* World);

	~Enemy();

	friend class RenderManager;
};

