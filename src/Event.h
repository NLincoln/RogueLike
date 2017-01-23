#pragma once

#include "Common.h"
#include <functional>

enum class EventType : uint
{
  NO_EVENT,

  EXIT_GAME,

  /* Movement Events */
  MOVE_LEFT,
  MOVE_RIGHT,
  MOVE_UP,
  MOVE_DOWN,

  /* Numkey Events */
  NUMPAD_0,
  NUMPAD_1,
  NUMPAD_2,
  NUMPAD_3,
  NUMPAD_4,
  NUMPAD_5,
  NUMPAD_6,
  NUMPAD_7,
  NUMPAD_8,
  NUMPAD_9,

  /* Game Events */
  ENEMY_DEATH,
  PLAYER_DEATH,

};

using EventRange = std::pair<EventType, EventType>;
using EventCallback = std::function<void(EventType)>;


namespace ERange
{
  const EventRange Movement = { EventType::MOVE_LEFT, EventType::MOVE_DOWN };
  const EventRange NumKey = { EventType::NUMPAD_0, EventType::NUMPAD_9 };
}

class EventManager
{
  std::map<EventType, std::vector<EventCallback>> m_Callbacks;

  EventType HandleKeyPressed(sf::Event KeyEvent);

public:
  void AddHook(const EventRange Range, EventCallback Callback);
  void AddHook(const EventType  Type, EventCallback Callback);

  void HandleEvent(EventType Event);
  void ProcessSFMLEvent(sf::Event Event);
  EventManager();
  ~EventManager();
};

