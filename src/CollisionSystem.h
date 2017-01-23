#pragma once
#include "Entity.h"
#include <functional>

using CollisionCallback = std::function<Entity*(WorldPos)>;

class CollisionSystem
{
  std::vector<Entity*> m_Entities;
public:
  void AddEntity(Entity* NewEntity);
  void RemoveEntity(Entity* ToRemove);
  CollisionCallback GetCallback();

  CollisionSystem();
  ~CollisionSystem();
};

