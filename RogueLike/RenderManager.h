#pragma once

#include <SFML/Graphics.hpp>

class Player;
class Entity;

class RenderManager
{
	Player* m_PlayerRef;

	sf::RenderTarget* m_RenderTarget;
	std::vector<Entity*> m_Entities;

public:
	void AddEntity(Entity* ent);
	void RemoveEntity(Entity* ToRemove);

	void SetRenderTarget(sf::RenderTarget* target);

	void Draw();

	RenderManager(Player* Player);
	~RenderManager();
};

