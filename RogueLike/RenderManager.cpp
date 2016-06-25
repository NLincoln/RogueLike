#include "RenderManager.h"

inline void RenderManager::AddElement(Renderable* elem)
{
    m_List.push_back(elem);
}

void RenderManager::Render(sf::RenderTarget& Target)
{
    for (Renderable* r : m_List)
    {
        Target.draw(*r);
    }
}
