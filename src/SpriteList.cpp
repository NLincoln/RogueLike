#include "SpriteList.h"
#include "RenderCommon.h"

void SpriteList::SetWidth(uint Width)
{
  m_Width = Width;
}

void SpriteList::SetWorldPos(WorldPos Pos)
{
  m_WorldPos = Pos;
  setPosition(m_WorldPos.x * SPRITE_WIDTH, m_WorldPos.y * SPRITE_HEIGHT);
}

void SpriteList::AddSprite(sf::Sprite Sprite)
{
  m_SpriteList.push_back(Sprite);
}

void SpriteList::SetColor(sf::Color Color)
{
  for (auto& Sprite : m_SpriteList)
    Sprite.setColor(Color);
}

SpriteList::SpriteList()
{
  m_Width = 0;
}

SpriteList::~SpriteList()
{
}

void SpriteList::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  auto BlockPos = getPosition();
  for (auto sprite : m_SpriteList)
  {
    auto SpritePos = sprite.getPosition();
    SpritePos += BlockPos;
    sprite.setPosition(SpritePos);
    target.draw(sprite);
  }
}
