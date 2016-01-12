#pragma once
#include "Common.h"

#include <SFML/Graphics.hpp>
using WorldPos = sf::Vector2u;

class SpriteBlock : public sf::Drawable, public sf::Transformable
{
	std::vector<sf::Sprite> m_SpriteList;
	WorldPos m_WorldPos;

public:
	void SetWorldPos(WorldPos Pos);

	void AddSprite(sf::Sprite Sprite);

	void SetColor(sf::Color Color);

	SpriteBlock();
	~SpriteBlock();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;


};

