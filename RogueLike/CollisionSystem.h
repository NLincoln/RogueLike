#pragma once
#include "Entity.h"
#include <functional>

using CollisionCallback = std::function<bool(WorldPos)>;

class CollisionSystem
{
	std::vector<Entity*> m_Entities;
public:
	void AddEntity(Entity* NewEntity);
	CollisionCallback GetCallback();

	CollisionSystem();
	~CollisionSystem();
};

