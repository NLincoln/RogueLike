#include "RenderManager.h"
#include "Entity.h"
#include "Player.h"
#include "Enemy.h"
#include <string>

void HUDSystem::AddHook(std::function<std::string()> Hook)
{
  m_HudCallbacks.push_back(Hook);
}

void HUDSystem::RemoveHook(std::function<std::string()> Hook)
{
  //m_HudCallbacks.erase(std::find(m_HudCallbacks.begin(), m_HudCallbacks.end(), Hook));
}

SpriteList HUDSystem::Render(WorldPos Dims) const
{
  SpriteList Value;
  return Value;
}

HUDSystem& RenderManager::GetHUD()
{
  return m_Hud;
}

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
  sf::Rect<float> WorldBox; // Works in Render coordinates
  WorldBox.top = 0;
  WorldBox.left = 0;
  WorldBox.height = SCREEN_HEIGHT - 10 * SPRITE_HEIGHT;
  WorldBox.width = SCREEN_WIDTH - 10 * SPRITE_WIDTH;



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
      WorldPos Center = { WORLD_WIDTH / 2 - 16, WORLD_HEIGHT / 2 - 16};
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

      if (WorldBox.contains(RenderPos))
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
