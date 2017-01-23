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

void EnemyManager::AddEntity(Enemy* NewEntity)
{
  m_Entities.push_back(NewEntity);
}

WorldPos EnemyManager::GetPlayerLoc() const
{
  return m_PlayerRef->GetWorldPos();
}

EnemyManager::EnemyManager(EventManager& EventManager, MovementSystem& MovementSystem, Player* p)
{
  m_PlayerRef = p;
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
