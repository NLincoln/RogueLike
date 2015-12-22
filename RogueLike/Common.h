#pragma once

#include <SFML/Graphics.hpp>



using uint = unsigned int;

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

