#include "CollisionSystem.h"


void CollisionSystem::AddEntity(Entity* NewEntity)
{
	m_Entities.push_back(NewEntity);
}

CollisionCallback CollisionSystem::GetCallback()
{
	return [&] (WorldPos NewPos)
	{
		for (auto Entity : m_Entities)
			if (Entity->GetWorldPos() == NewPos)
				return false;
		return true;
	};
}

CollisionSystem::CollisionSystem()
{
}


CollisionSystem::~CollisionSystem()
{
}
