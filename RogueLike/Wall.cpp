#include "Wall.h"


Wall::Wall(SpriteBlock Sprite) : m_ObstructionComponent([] () {})
{
	m_Sprite = Sprite;
}


Wall::~Wall()
{
}
