#pragma once
#include "Component.h"
#include "Entity.h"

class Wall : public Entity
{
	Comp::Obstruction m_ObstructionComponent;

public:
	WorldPos MoveWorldPos(WorldPos delta) override { return m_WorldPos; }

	Wall(SpriteBlock Sprite);
	~Wall();
};

