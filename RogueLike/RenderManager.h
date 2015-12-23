#pragma once

#include <SFML/Graphics.hpp>

class Entity;

class RenderManager
{
	sf::RenderTarget* m_RenderTarget;
	std::vector<Entity*> m_Entities;

public:
	void AddEntity(Entity* ent);

	void SetRenderTarget(sf::RenderTarget* target);

	void Draw();

	RenderManager(sf::RenderTarget* target = nullptr);
	~RenderManager();
};

