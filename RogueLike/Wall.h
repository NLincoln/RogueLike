#pragma once
#include "ObstructionComponent.h"
#include "Entity.h"

class Wall : public Entity
{
	ObstructionComponent m_ObstructionComponent;

public:
	WorldPos MoveWorldPos(WorldPos delta) override { return m_WorldPos; }

	Wall();
	~Wall();
};

