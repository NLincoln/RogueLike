#pragma once

#include "Common.h"

using WorldPos = sf::Vector2u;
using RenderPos = sf::Vector2f;

const uint WINDOW_HEIGHT = 16 * 50;
const uint WINDOW_WIDTH = 16 * 80;

const uint SPRITE_HEIGHT = 16;
const uint SPRITE_WIDTH = 16;

const uint WORLD_HEIGHT = 50;
const uint WORLD_WIDTH = 80;

const uint SCREEN_HEIGHT = WORLD_HEIGHT * SPRITE_HEIGHT;
const uint SCREEN_WIDTH = WORLD_WIDTH  * SPRITE_WIDTH;