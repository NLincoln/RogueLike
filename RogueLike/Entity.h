#pragma once

#include <SFML/Graphics.hpp>

#include "SpriteBlock.h"
#include "RenderCommon.h"

class Entity : public sf::Drawable, public sf::Transformable
{
protected:
	WorldPos m_WorldPos;
	SpriteBlock m_Sprite;
public:
	WorldPos GetWorldPos() const;
	WorldPos MoveWorldPos(WorldPos delta);
	void SetWorldPos(WorldPos NewPos);

	void SetSprite(SpriteBlock sprite);


	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	Entity();
	~Entity();
};

