#include "EnemyManager.h"
#include "MovementSystem.h"
#include "Player.h"

void EnemyManager::AddHook(EventType Type, EventCallback Callback)
{
	m_EnemyCallbacks[Type].push_back(Callback);
}

void EnemyManager::AddHook(EventRange Range, EventCallback Callback)
{
	for (uint i = static_cast<uint>(Range.first); i <= static_cast<uint>(Range.second); ++i)
		AddHook(static_cast<EventType>(i), Callback);
}

EnemyManager::EnemyManager(MovementSystem& MovementSystem, Player* p)
{
	MovementSystem.AddHook(ERange::Movement, p, [&](EventType Type)
	{
		auto Callbacks = m_EnemyCallbacks[Type];
		for (auto Callback : Callbacks)
			Callback(Type);
	});
}

EnemyManager::~EnemyManager()
{
}
