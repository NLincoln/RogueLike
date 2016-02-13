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
		std::map<StateType, AIFunction> AIStates;

		auto MoveTowards = [](WorldPos Start, WorldPos Dest)
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

		auto HasLOS = [this]() mutable
		{
			auto Line = m_WorldRef->FindLine(m_WorldPos, m_EnemyManagerRef->GetPlayerLoc());
			for (auto point : Line)
			{
				if (dynamic_cast<Wall*>(point))
				{
					return false;
				}
			}
			return true;
		};

		auto Pursuit = [&AIStates, &MoveTowards, &HasLOS, this]() mutable
		{
			if (!HasLOS())
			{
				m_CurrentState = StateType::LastKnown;
				AIStates[m_CurrentState]();
				return;
			}
			m_PrevTarget = m_EnemyManagerRef->GetPlayerLoc();
			WorldPos NextPos = Move(m_WorldPos, MoveTowards(m_WorldPos, m_PrevTarget));

			Entity* Target = m_CollisionCallback(NextPos);
			if (Target == nullptr)
				m_WorldPos = NextPos;
			else if (auto Temp = dynamic_cast<Player*>(Target))
				if(!isDead())
					Temp->ReceiveDamage(CalculateDamage(m_Inventory[0], Temp));
		};

		AIStates.insert(std::make_pair<StateType, AIFunction>(StateType::Pursuit, Pursuit));

		auto Rest = [&AIStates, &HasLOS, this]() mutable
		{
			if (HasLOS())
			{
				m_CurrentState = StateType::Pursuit;
				AIStates[m_CurrentState]();
				return;
			}
			//Do nothing
		};

		AIStates.insert(std::make_pair<StateType, AIFunction>(StateType::Rest, Rest));

		auto LastKnown = [&]() mutable
		{
			if (HasLOS())
			{
				m_CurrentState = StateType::Pursuit;
				AIStates[m_CurrentState]();
				return;
			}
			if (m_WorldPos == m_PrevTarget)
			{
				m_CurrentState = StateType::Rest;
				AIStates[m_CurrentState]();
				return;
			}
			m_WorldPos = Move(m_WorldPos, MoveTowards(m_WorldPos, m_PrevTarget));
		};
		AIStates.insert(std::make_pair<StateType, AIFunction>(StateType::LastKnown, LastKnown));

		AIStates[m_CurrentState]();
	};
}

bool Enemy::isDead() const
{
	return m_Health <= m_DeathHP;
}

void Enemy::ReceiveDamage(int Damage)
{
	m_Health -= Damage;
	if (isDead())
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

	m_CurrentState = StateType::Rest;
	MovementCallback()(EventType::NO_EVENT); // Doesn't matter what kind, just need to run this once.
	return;
}

Enemy::~Enemy()
{
}
