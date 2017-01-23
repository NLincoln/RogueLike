#include "SpriteFactory.h"
#include <cctype>
#include "SpriteList.h"
#include "RenderCommon.h"

SpriteList SpriteFactory::CreateFromText(std::string Text)
{
  SpriteList Result;
  sf::Sprite sprite;
  
  uint offset = 0;
  for (auto c : Text)
  {   
    sprite.setTexture(m_Textures[static_cast<SPRITENAMES>(c)]);
    sprite.setPosition(sf::Vector2f(offset, 0));
    Result.AddSprite(sprite);
    offset += SPRITE_WIDTH;
  }

  return Result;
}

SpriteList SpriteFactory::CreateFromSpriteName(SPRITENAMES name)
{
  SpriteList Result;
  sf::Sprite Sprite;
  Sprite.setTexture(m_Textures[name]);
  Result.AddSprite(Sprite);
  return Result;
}

SpriteList SpriteFactory::operator[](SPRITENAMES name)
{
  return CreateFromSpriteName(name);
}

SpriteList SpriteFactory::operator[](std::string Text)
{
  return CreateFromText(Text);
}

SpriteFactory::SpriteFactory(std::string Filename)
{
  for (uint i = 0; i < SHEET_HEIGHT; ++i)
  {
    for (uint j = 0; j < SHEET_WIDTH; ++j)
    {
      sf::Texture Temp;
      sf::IntRect Rect;
      Rect.width = SPRITE_WIDTH;
      Rect.height = SPRITE_HEIGHT;
      Rect.top = i * SPRITE_HEIGHT;
      Rect.left = j * SPRITE_WIDTH;

      Temp.loadFromFile(Filename, Rect);
      m_Textures.insert(std::make_pair(static_cast<SPRITENAMES>(i * SHEET_WIDTH + j), Temp));
    }
  }
}


SpriteFactory::~SpriteFactory()
{
}
