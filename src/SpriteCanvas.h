#pragma once
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <vector>
#include "SpriteList.h"

class SpriteCanvas : public sf::Drawable, public sf::Transformable
{
  sf::Vector2u Size;
  std::vector<SpriteList> Canvas;
  WorldPos WorldPos;

public:
  sf::Sprite& operator()(sf::Vector2u);
  sf::Sprite& operator()(uint x, uint y);

  SpriteCanvas(sf::Vector2u size);
  ~SpriteCanvas();

  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

