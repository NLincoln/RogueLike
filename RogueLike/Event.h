#pragma once

#include "Common.h"
#include <functional>
#include <stack>

enum class EventType : uint
{
	NO_EVENT,

	/* Movement Events */
	MOVE_LEFT,
	MOVE_RIGHT,
	MOVE_UP,
	MOVE_DOWN,
};
using EventRange = std::pair<EventType, EventType>;
using EventCallback = std::function<void(EventType)>;


namespace ERange
{
	const EventRange Movement = { EventType::MOVE_LEFT, EventType::MOVE_DOWN };
}
class EventManager
{
	std::map<EventType, std::stack<EventCallback>> m_Callbacks;

	EventType HandleKeyPressed(sf::Event KeyEvent);
	void HandleEvent(EventType Event);

public:
	void AddHook(const EventRange Range, EventCallback Callback);
	void AddHook(const EventType  Type, EventCallback Callback);

	void ReleaseHook(const EventRange Range);
	void ReleaseHook(const EventType Type);

	void ProcessSFMLEvent(sf::Event Event);
	EventManager();
	~EventManager();
};

