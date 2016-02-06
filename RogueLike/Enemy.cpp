#include "Enemy.h"
#include "EnemyManager.h"
#include "Item.h"
#include "CollisionSystem.h"
#include "EntityCommon.h"
#include "Player.h"
#include "Event.h"
#include "RenderManager.h"
#include "DamageSystem.h"

std::function<void(EventType)> Enemy::MovementCallback()
{
	return [&](EventType Type)
	{
		WorldPos NextPos = Move(m_WorldPos, Type, 1);
		Entity* Result = m_CollisionCallback(NextPos);
		if (Result == nullptr)
			m_WorldPos = NextPos;



		else if (auto Temp = dynamic_cast<Player*>(Result))
		{
			Temp->ReceiveDamage(CalculateDamage(m_Inventory[0], Temp));
		}
	};
}

bool Enemy::isDead() const
{
	return m_Health <= m_DeathHP;
}

void Enemy::ReceiveDamage(int Damage)
{
	m_Health -= Damage;
	if (m_Health <= m_DeathHP)
		m_EventManagerRef->HandleEvent(EventType::ENEMY_DEATH);
}

Enemy::Enemy(RenderManager& RenderManager, CollisionSystem& CollisionSystem, EnemyManager& EnemyManager, EventManager* EventManager, WorldGenerator* World)
{
	m_Health = 100;
	m_DeathHP = 0;

	m_WorldRef = World;
	m_EventManagerRef = EventManager;

	Item Sword;
	Sword.SetDamage(40);
	m_Inventory.push_back(Sword);

	RenderManager.AddEntity(this);
	CollisionSystem.AddEntity(this);
	m_CollisionCallback = CollisionSystem.GetCallback();
	EnemyManager.AddHook(ERange::Movement, MovementCallback());

	EventManager->AddHook(EventType::ENEMY_DEATH, [&] (EventType Type)
	{
		RenderManager.RemoveEntity(this);
		CollisionSystem.RemoveEntity(this);
	});

}

Enemy::~Enemy()
{
}
