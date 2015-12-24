#pragma once

#include "Common.h"
#include <functional>

enum class EventType : uint
{
	NO_EVENT,

	/* Movement Events */
	MOVE_LEFT,
	MOVE_RIGHT,
	MOVE_UP,
	MOVE_DOWN,

	/* Context Switches */
	SWITCH_PLAYER,
	// More as they come...
	SWITCH_CURSOR,
};

enum class EventContext
{
	NO_CONTEXT,
	PLAYER_FOCUS,
};

using EventRange = std::pair<EventType, EventType>;
using EventCallback = std::function<void(EventType)>;
using EventContextPair = std::pair<EventContext, EventType>;


namespace ERange
{
	const EventRange Movement = { EventType::MOVE_LEFT, EventType::MOVE_DOWN };
	const EventRange ContextSwitch = { EventType::SWITCH_PLAYER, EventType::SWITCH_CURSOR };
}
class EventManager
{
	std::map<EventContextPair, std::vector<EventCallback>> m_Callbacks;

	EventContext CurrentContext;

	EventType HandleKeyPressed(sf::Event KeyEvent);
	void HandleEvent(EventType Event);

public:
	void AddHook(const EventRange Range, const EventContext Context, EventCallback Callback);
	void AddHook(const EventType  Type, const EventContext Context, EventCallback Callback);

	void ProcessSFMLEvent(sf::Event Event);
	EventManager();
	~EventManager();
};

