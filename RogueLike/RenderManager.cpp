#include "RenderManager.h"
#include "RenderCommon.h"

#include "Entity.h"

void RenderManager::AddEntity(Entity* ent)
{
	if(ent) m_Entities.push_back(ent);
}

void RenderManager::SetRenderTarget(sf::RenderTarget* target)
{
	m_RenderTarget = target;
}

void RenderManager::Draw()
{
	for (Entity* entity : m_Entities)
		m_RenderTarget->draw(*entity);
	
}

RenderManager::RenderManager()
{
}


RenderManager::~RenderManager()
{
}
