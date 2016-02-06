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

void RenderManager::SetRenderTarget(sf::RenderTarget* target)
{
	m_RenderTarget = target;
}

void RenderManager::Draw() const
{
	if(m_RenderTarget)
		for (auto entity : m_Entities)
		{
			auto Block = entity->m_Sprite;
			Block.setPosition(entity->GetWorldPos().x * SPRITE_WIDTH, entity->GetWorldPos().y * SPRITE_HEIGHT);

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

RenderManager::RenderManager(Player* Player)
{
	m_RenderTarget = nullptr;
	m_PlayerRef = Player;
}


RenderManager::~RenderManager()
{
}
