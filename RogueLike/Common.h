#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

using uint = unsigned int;
using WorldPos = sf::Vector2u;

const uint SPRITE_HEIGHT = 16;
const uint SPRITE_WIDTH = 16;

const uint WORLD_WIDTH = 80;
const uint WORLD_HEIGHT = 50;

const uint WINDOW_HEIGHT = SPRITE_HEIGHT * WORLD_HEIGHT;
const uint WINDOW_WIDTH = SPRITE_WIDTH * WORLD_WIDTH;

#ifdef _WIN32

#ifdef _DEBUG
#pragma comment (lib, "sfml-main-d.lib")
#pragma comment (lib, "sfml-system-d.lib")
#pragma comment (lib, "sfml-window-d.lib")
#pragma comment (lib, "sfml-graphics-d.lib")
#elif
#pragma comment (lib, "sfml-main.lib")
#pragma comment (lib, "sfml-system.lib")
#pragma comment (lib, "sfml-window.lib")
#pragma comment (lib, "sfml-graphics.lib")
#endif

#endif