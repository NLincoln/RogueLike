#include "Player.h"
#include "Event.h"
#include "MovementSystem.h"
#include <functional>
#include "EntityCommon.h"
#include "Enemy.h"
#include "DamageSystem.h"
#include "RenderManager.h"
#include "Wall.h"

void Player::ReceiveDamage(int Damage)
{
  m_Health -= Damage;
  if (m_Health <= m_DeathHP)
    m_EventManagerRef->HandleEvent(EventType::PLAYER_DEATH);
}

std::function<void(EventType)> Player::MovementCallback()
{
  return [&](EventType Type)
  {
    WorldPos NewPos = Move(m_WorldPos, Type, 1);

    Entity* Result = m_CollisionCallback(NewPos);

    if (dynamic_cast<Wall*>(Result))
      return; //What can mere men do against such an obstacle?
    if (auto Temp = dynamic_cast<Enemy*>(Result))
      Temp->ReceiveDamage(CalculateDamage(m_Inventory[0], Temp));
    if (Result == nullptr)
      m_WorldPos = NewPos;
  };
}

Player::Player(const SpriteList sprite,
             RenderManager& RenderManager, 
             MovementSystem& MovementSystem, 
             CollisionSystem& CollisionSystem, 
             EventManager* EventManager, 
             WorldGenerator* WorldGenerator)
{
  m_Health = 100;
  m_DeathHP = 0;

  m_WorldRef = WorldGenerator;
  m_EventManagerRef = EventManager;
  m_Sprite = sprite;
  CollisionSystem.AddEntity(this);
  m_CollisionCallback = CollisionSystem.GetCallback();

  RenderManager.AddEntity(this);

  Item Item;
  Item.SetDamage(40);
  m_Inventory.push_back(Item);

  MovementSystem.AddHook(ERange::Movement, this, MovementCallback());


}

Player::~Player()
{
}
