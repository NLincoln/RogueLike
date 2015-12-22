#pragma once
#include "Common.h"

#include <SFML/Graphics.hpp>

class SpriteBlock : public sf::Drawable, public sf::Transformable
{
	std::vector<sf::Sprite> m_SpriteList;
public:
	void AddSprite(sf::Sprite Sprite);

	SpriteBlock();
	~SpriteBlock();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;


};

