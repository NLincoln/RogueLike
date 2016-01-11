#include "Enemy.h"
#include "EnemyManager.h"
#include "Item.h"
#include "CollisionSystem.h"
#include "EntityCommon.h"
#include "Player.h"
#include "Event.h"

void Enemy::ReceiveDamage(int Damage)
{
	m_Health -= Damage;
	if (m_Health < 0)
		m_EventManagerRef->HandleEvent(EventType::ENEMY_DEATH);
}

Enemy::Enemy(CollisionSystem& CollisionSystem, EnemyManager& EnemyManager, EventManager* EventManager) 
{
	m_EventManagerRef = EventManager;
	Item Sword;
	Sword.SetDamage(40);
	m_Inventory.push_back(Sword);

	CollisionSystem.AddEntity(this);
	m_CollisionCallback = CollisionSystem.GetCallback();
	EnemyManager.AddHook(ERange::Movement, [&] (EventType Type)
	{
		WorldPos NextPos = Move(m_WorldPos, Type, 1);
		Entity* Result = m_CollisionCallback(NextPos);
		if (Result == nullptr)
			m_WorldPos = NextPos;
		else if (dynamic_cast<Player*>(Result))
		{
			
		}
	});
}

Enemy::~Enemy()
{
}
