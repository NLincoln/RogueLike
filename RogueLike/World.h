#pragma once
#include "Entity.h"
#include "SpriteFactory.h"
#include "CollisionSystem.h"

class RenderManager;

class WorldGenerator
{
	std::vector<Entity*> m_Entities;
	sf::Vector2u m_Dimensions;


public:
	void CreateRandom(RenderManager& RenderManager, CollisionSystem& CollisionSystem, SpriteFactory& SpriteFactory);
	Entity* operator[](WorldPos Coords);
	Entity* operator()(WorldPos Coords);

	Entity* At(WorldPos Coords);

	std::vector<Entity*> FindLine(WorldPos Start, WorldPos End);
	std::vector<Entity*> CalcFOV(WorldPos Position);


	WorldGenerator(sf::Vector2u Dimensions);
	~WorldGenerator();
};

