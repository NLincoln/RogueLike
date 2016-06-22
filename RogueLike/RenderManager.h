#pragma once

#include <SFML/Graphics.hpp>
#include <functional>
#include "World.h"

class SpriteList;
class Player;
class Entity;

class HUDSystem
{
	std::vector<std::function<std::string()>> m_HudCallbacks;
	void RemoveHook(std::function<std::string()> Hook);

public:
	void AddHook(std::function<std::string()> Hook);


	SpriteList Render(WorldPos Dims) const;

};

class RenderManager
{
	HUDSystem m_Hud;

	Entity* m_FocusEntity;

	sf::RenderTarget* m_RenderTarget;
	std::vector<Entity*> m_Entities;

public:
	HUDSystem& GetHUD();

	void AddEntity(Entity* ent);
	void RemoveEntity(Entity* ToRemove);

	void SetFocus(Entity* Focus);

	void SetRenderTarget(sf::RenderTarget* target);

	void Draw() const;

	RenderManager(Entity* Focus = nullptr);
	~RenderManager();
};

