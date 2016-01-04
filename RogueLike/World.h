#pragma once
#include "Entity.h"
#include "SpriteFactory.h"
#include "CollisionSystem.h"

class RenderManager;

class World
{
	std::vector<Entity*> m_Entities;
	sf::Vector2u m_Dimensions;

	Entity* At(WorldPos Coords);

public:
	void CreateRandom(RenderManager& RenderManager, CollisionSystem& CollisionSystem, SpriteFactory& SpriteFactory);
	Entity* operator[](WorldPos Coords);


	World(sf::Vector2u Dimensions);
	~World();
};

