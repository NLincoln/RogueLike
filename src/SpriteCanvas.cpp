#include "SpriteCanvas.h"



SpriteCanvas::SpriteCanvas(sf::Vector2u size) : Size(size)
{

}


sf::Sprite& SpriteCanvas::operator()(sf::Vector2u loc)
{
	return Canvas[loc.x].m_SpriteList[loc.y];
}

sf::Sprite& SpriteCanvas::operator()(uint x, uint y)
{
	return operator()(sf::Vector2u(x, y));
}

SpriteCanvas::~SpriteCanvas()
{
}

void SpriteCanvas::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (auto List : Canvas)
	{
	}
}
