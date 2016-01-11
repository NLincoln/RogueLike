#include "CollisionSystem.h"


void CollisionSystem::AddEntity(Entity* NewEntity)
{
	if (NewEntity)
		m_Entities.push_back(NewEntity);
	
}

CollisionCallback CollisionSystem::GetCallback()
{
	return [&] (WorldPos NewPos)
	{
		for (auto Entity : m_Entities)
			if (Entity->GetWorldPos() == NewPos)
				return Entity;
		return static_cast<Entity*>(nullptr);
	};
}

CollisionSystem::CollisionSystem()
{
}


CollisionSystem::~CollisionSystem()
{
}
