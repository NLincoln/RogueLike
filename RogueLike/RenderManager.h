#pragma once

#include <SFML/Graphics.hpp>

class Player;
class Entity;

class RenderManager
{
	Entity* m_FocusEntity;

	sf::RenderTarget* m_RenderTarget;
	std::vector<Entity*> m_Entities;

public:
	void AddEntity(Entity* ent);
	void RemoveEntity(Entity* ToRemove);

	void SetFocus(Entity* Focus);

	void SetRenderTarget(sf::RenderTarget* target);

	void Draw() const;

	RenderManager(Entity* Focus = nullptr);
	~RenderManager();
};

