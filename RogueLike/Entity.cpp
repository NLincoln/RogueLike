#include "Entity.h"


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

void Entity::SetSprite(SpriteBlock sprite)
{
	m_Sprite = sprite;
}

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	SpriteBlock copy = m_Sprite;

	RenderPos RenderPos;
	RenderPos.x = m_WorldPos.x * SPRITE_WIDTH;
	RenderPos.y = m_WorldPos.y * SPRITE_HEIGHT;

	copy.setPosition(RenderPos);

	target.draw(copy);
}

Entity::Entity()
{
}


Entity::~Entity()
{
}
