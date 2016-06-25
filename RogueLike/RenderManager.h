#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

class Renderable : public sf::Drawable
{
    
};

class RenderManager
{
    std::vector<Renderable*> m_List;
public:
    void AddElement(Renderable* elem);
    void Render(sf::RenderTarget& Target);
};

