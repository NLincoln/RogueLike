#include "RenderManager.h"
#include "Entity.h"
#include "Player.h"
#include "Enemy.h"

void RenderManager::AddEntity(Entity* ent)
{
	if(ent)
		m_Entities.push_back(ent);
}

void RenderManager::RemoveEntity(Entity* ToRemove)
{
	m_Entities.erase(std::find(m_Entities.begin(), m_Entities.end(), ToRemove));
}

void RenderManager::SetFocus(Entity* Focus)
{
	m_FocusEntity = Focus;
}

void RenderManager::SetRenderTarget(sf::RenderTarget* target)
{
	m_RenderTarget = target;
}

void RenderManager::Draw() const
{

	if(m_RenderTarget && m_FocusEntity)
	{
		WorldPos FocusLoc = m_FocusEntity->GetWorldPos();
		for (auto entity : m_Entities)
		{
			auto Block = entity->m_Sprite;
			WorldPos BlockPos = entity->GetWorldPos();
			sf::Vector2f RenderPos = {};
			WorldPos ScreenPos = {};
			WorldPos Delta = BlockPos - FocusLoc;
			WorldPos Center = { WORLD_WIDTH / 2, WORLD_HEIGHT / 2 };
			ScreenPos = Center + Delta;
			RenderPos.x = ScreenPos.x * SPRITE_WIDTH;
			RenderPos.y = ScreenPos.y * SPRITE_HEIGHT;

			Block.setPosition(RenderPos);

			// Class-specific code goes here:
			// Also, this should definitely be replaced by something that doesn't go here. 
			// Caching may be the answer to our problems. But then we get to deal with the fun of 
			// Cache-invalidation.

			if (auto Temp = dynamic_cast<Player*>(entity))
			{
			}
			if (auto Temp = dynamic_cast<Enemy*>(entity))
			{
				sf::Uint8 DisplayColor = Temp->m_Health / static_cast<double>(Temp->m_MaxHP) * 255;
				Block.SetColor(sf::Color(255, DisplayColor, DisplayColor));
			}
			m_RenderTarget->draw(Block);
		}
	}
}

RenderManager::RenderManager(Entity* Focus)
{
	m_RenderTarget = nullptr;
	m_FocusEntity = Focus;
}


RenderManager::~RenderManager()
{
}
