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

		auto MoveTowards = [] (WorldPos Start, WorldPos Dest)
		{
			direction result;

			sf::Vector2i delta = sf::Vector2i(Dest.x - Start.x, Dest.y - Start.y);
			if (delta.x > 0 && abs(delta.x) > abs(delta.y))
				result = direction::East;
			else if (delta.x <= 0 && abs(delta.x) > abs(delta.y))
				result = direction::West;
			else if (delta.y > 0 && abs(delta.y) > abs(delta.x))
				result = direction::South;
			else
				result = direction::North;
			return result;
		};

		if (HasLOS)
		{
			m_PrevTargetIsSet = true;
			WorldPos PlayerLoc = m_EnemyManagerRef->GetPlayerLoc();
			m_PrevTarget = PlayerLoc;
			WorldPos NextPos = Move(m_WorldPos, MoveTowards(m_WorldPos, PlayerLoc));

			Entity* Result = m_CollisionCallback(NextPos);
			if (Result == nullptr)
				m_WorldPos = NextPos;
			else if (auto Temp = dynamic_cast<Player*>(Result))
				if (m_Health > m_DeathHP)
					Temp->ReceiveDamage(CalculateDamage(m_Inventory[0], Temp));
		}
		else
		{
			if(m_PrevTargetIsSet)
				m_WorldPos = Move(m_WorldPos, MoveTowards(m_WorldPos, m_PrevTarget));
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
	if (!isDead())
		m_EventManagerRef->HandleEvent(EventType::ENEMY_DEATH);
}

Enemy::Enemy(RenderManager& RenderManager, CollisionSystem& CollisionSystem, EnemyManager* EnemyManager, EventManager* EventManager, WorldGenerator* World)
{
	m_PrevTargetIsSet = false;
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
