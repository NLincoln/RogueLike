#include "Wall.h"


Wall::Wall(SpriteList Sprite) : m_ObstructionComponent([] () {})
{
	m_Sprite = Sprite;
}


Wall::~Wall()
{
}
