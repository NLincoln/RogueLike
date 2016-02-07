#include "Enemy.h"
#include "EnemyManager.h"
#include "Item.h"
#include "CollisionSystem.h"
#include "EntityCommon.h"
#include "Player.h"
#include "Event.h"
#include "RenderManager.h"
#include "DamageSystem.h"
#include "Wall.h"

std::function<void(EventType)> Enemy::MovementCallback()
{
	return [&](EventType Type)
	{
		auto Line = m_WorldRef->FindLine(m_WorldPos, m_EnemyManagerRef->GetPlayerLoc());
		bool HasLOS = true;

		for (auto point : Line)
		{
			if (dynamic_cast<Wall*>(point))
			{
				HasLOS = false;
				break;
			}
		}
		if (HasLOS)
		{
			WorldPos PlayerLoc = m_EnemyManagerRef->GetPlayerLoc();
			WorldPos NextPos;

			sf::Vector2i delta = sf::Vector2i(PlayerLoc.x - m_WorldPos.x, PlayerLoc.y - m_WorldPos.y);
			if (delta.x > 0 && abs(delta.x) > abs(delta.y))
				NextPos = Move(m_WorldPos, direction::East);
			else if (delta.x <= 0 && abs(delta.x) > abs(delta.y))
				NextPos = Move(m_WorldPos, direction::West);
			else if (delta.y > 0 && abs(delta.y) > abs(delta.x))
				NextPos = Move(m_WorldPos, direction::South);
			else
				NextPos = Move(m_WorldPos, direction::North);

			Entity* Result = m_CollisionCallback(NextPos);
			if (Result == nullptr)
				m_WorldPos = NextPos;

			else if (auto Temp = dynamic_cast<Player*>(Result))
			{
				Temp->ReceiveDamage(CalculateDamage(m_Inventory[0], Temp));
			}
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

Enemy::Enemy(RenderManager& RenderManager, CollisionSystem& CollisionSystem, EnemyManager* EnemyManager, EventManager* EventManager, WorldGenerator* World)
{
	m_Health  = m_MaxHP = 100;
	m_DeathHP = 0;

	m_WorldRef = World;
	m_EventManagerRef = EventManager;
	m_EnemyManagerRef = EnemyManager;
	Item Sword;
	Sword.SetDamage(40);
	m_Inventory.push_back(Sword);

	RenderManager.AddEntity(this);
	CollisionSystem.AddEntity(this);
	m_CollisionCallback = CollisionSystem.GetCallback();
	EnemyManager->AddHook(ERange::Movement, MovementCallback());

	EventManager->AddHook(EventType::ENEMY_DEATH, [&] (EventType Type)
	{
		RenderManager.RemoveEntity(this);
		CollisionSystem.RemoveEntity(this);
	});

}

Enemy::~Enemy()
{
}
