#pragma once
#include "Entity.h"
#include "SpriteFactory.h"
#include "CollisionSystem.h"

class RenderManager;

class WorldGenerator
{
	std::vector<Entity*> m_Entities;
	sf::Vector2u m_Dimensions;

	Entity* At(WorldPos Coords);

public:
	void CreateRandom(RenderManager& RenderManager, CollisionSystem& CollisionSystem, SpriteFactory& SpriteFactory);
	Entity* operator[](WorldPos Coords);


	WorldGenerator(sf::Vector2u Dimensions);
	~WorldGenerator();
};

