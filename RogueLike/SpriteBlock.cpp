#include "SpriteBlock.h"


void SpriteBlock::AddSprite(sf::Sprite Sprite)
{
	m_SpriteList.push_back(Sprite);
}

SpriteBlock::SpriteBlock()
{
}


SpriteBlock::~SpriteBlock()
{
}

void SpriteBlock::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	auto BlockPos = getPosition();
	for (auto sprite : m_SpriteList)
	{
		auto SpritePos = sprite.getPosition();
		SpritePos += BlockPos;
		sprite.setPosition(SpritePos);
		target.draw(sprite);
	}
}
