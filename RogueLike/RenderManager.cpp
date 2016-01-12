#include "RenderManager.h"
#include "Entity.h"

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

void RenderManager::Draw()
{
	if(m_RenderTarget)
		for (auto entity : m_Entities)
			m_RenderTarget->draw(*entity);	
}

RenderManager::RenderManager(sf::RenderTarget* target)
{
	m_RenderTarget = target;
}


RenderManager::~RenderManager()
{
}
