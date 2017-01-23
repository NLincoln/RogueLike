#pragma once

#include <SFML/Graphics.hpp>

#include "SpriteList.h"
#include "RenderCommon.h"

struct EntityDescription
{

};

class Entity : public sf::Drawable, public sf::Transformable
{
protected:
	WorldPos m_WorldPos;
	SpriteList m_Sprite;

public:
	WorldPos GetWorldPos() const;
	virtual WorldPos MoveWorldPos(WorldPos delta);
	void SetWorldPos(WorldPos NewPos);

	void SetSprite(SpriteList sprite);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	Entity();
	~Entity();

	friend class RenderManager;
};

