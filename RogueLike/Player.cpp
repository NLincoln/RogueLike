#include "Player.h"
#include "Event.h"
#include "MovementSystem.h"
#include <functional>
#include "EntityCommon.h"
#include "Enemy.h"
#include "DamageSystem.h"

Player::Player(const SpriteBlock sprite, MovementSystem& MovementSystem, CollisionSystem& CollisionSystem)
{
	m_Sprite = sprite;
	CollisionSystem.AddEntity(this);
	m_CollisionCallback = CollisionSystem.GetCallback();

	Item Item;
	Item.SetDamage(40);
	m_Inventory.push_back(Item);

	MovementSystem.AddHook(ERange::Movement, this, [&] (EventType Event)
					{
						WorldPos NewPos = Move(m_WorldPos, Event, 1);

						Entity* Result = m_CollisionCallback(NewPos);

						if (Result == nullptr)
							m_WorldPos = NewPos;
						else if (auto Temp = dynamic_cast<Enemy*>(Result))
						{
							Temp->ReceiveDamage(CalculateDamage(m_Inventory[0], Temp));
						}
					});
}

Player::~Player()
{
}
