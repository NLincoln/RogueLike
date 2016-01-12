#include "Enemy.h"
#include "EnemyManager.h"
#include "Item.h"
#include "CollisionSystem.h"
#include "EntityCommon.h"
#include "Player.h"
#include "Event.h"
#include "RenderManager.h"

bool Enemy::isDead() const
{
	return m_Health <= m_DeathHP;
}

void Enemy::ReceiveDamage(int Damage)
{
	m_Health -= Damage;
	if (m_Health <= m_DeathHP)
		m_EventManagerRef->HandleEvent(EventType::ENEMY_DEATH);
	m_Sprite.SetColor(sf::Color(m_Health, 0, 0));
}

Enemy::Enemy(RenderManager& RenderManager, CollisionSystem& CollisionSystem, EnemyManager& EnemyManager, EventManager* EventManager)
{
	m_Health = 100;
	m_DeathHP = 0;

	m_EventManagerRef = EventManager;

	Item Sword;
	Sword.SetDamage(40);
	m_Inventory.push_back(Sword);

	RenderManager.AddEntity(this);
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

	EventManager->AddHook(EventType::ENEMY_DEATH, [&] (EventType Type)
	{
		RenderManager.RemoveEntity(this);
		CollisionSystem.RemoveEntity(this);
	});

}

Enemy::~Enemy()
{
}
