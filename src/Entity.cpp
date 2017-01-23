#include "Entity.h"
#include "Player.h"


WorldPos Entity::GetWorldPos() const
{
  return m_WorldPos;
}

WorldPos Entity::MoveWorldPos(WorldPos delta)
{
  m_WorldPos += delta;
  return m_WorldPos;
}

void Entity::SetWorldPos(WorldPos NewPos)
{
  m_WorldPos = NewPos;
}

void Entity::SetSprite(SpriteList sprite)
{
  m_Sprite = sprite;
}

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  // This is all handled in the RenderManager now!
}

Entity::Entity()
{
}


Entity::~Entity()
{
}
