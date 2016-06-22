#pragma once
#include "Common.h"

#include <SFML/Graphics.hpp>
using WorldPos = sf::Vector2u;

class SpriteList : public sf::Drawable, public sf::Transformable
{
	std::vector<sf::Sprite> m_SpriteList;
	WorldPos m_WorldPos;

	uint m_Width;

public:
	void SetWidth(uint Width);

	void SetWorldPos(WorldPos Pos);

	void AddSprite(sf::Sprite Sprite);

	void SetColor(sf::Color Color);

	SpriteList();
	~SpriteList();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	friend class SpriteCanvas;
};

