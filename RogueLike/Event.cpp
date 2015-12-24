#include <SFML/Window.hpp>
#include <map>
#include "Event.h"


void EventManager::ProcessSFMLEvent(sf::Event Event)
{
	EventType type = EventType::NO_EVENT;

	switch(Event.type)
	{
	case sf::Event::Closed: break;
	case sf::Event::Resized: break;
	case sf::Event::LostFocus: break;
	case sf::Event::GainedFocus: break;
	case sf::Event::TextEntered: break;
	case sf::Event::KeyPressed: 
		type = HandleKeyPressed(Event);
		break;
	case sf::Event::KeyReleased: break;
	case sf::Event::MouseWheelMoved: break;
	case sf::Event::MouseWheelScrolled: break;
	case sf::Event::MouseButtonPressed: break;
	case sf::Event::MouseButtonReleased: break;
	case sf::Event::MouseMoved: break;
	case sf::Event::MouseEntered: break;
	case sf::Event::MouseLeft: break;
	case sf::Event::JoystickButtonPressed: break;
	case sf::Event::JoystickButtonReleased: break;
	case sf::Event::JoystickMoved: break;
	case sf::Event::JoystickConnected: break;
	case sf::Event::JoystickDisconnected: break;
	case sf::Event::TouchBegan: break;
	case sf::Event::TouchMoved: break;
	case sf::Event::TouchEnded: break;
	case sf::Event::SensorChanged: break;
	case sf::Event::Count: break;
	default: break;
	}

	if(type != EventType::NO_EVENT)
		HandleEvent(type);
}

EventManager::EventManager() : CurrentContext(EventContext::PLAYER_FOCUS)
{
}

EventManager::~EventManager()
{
}

EventType EventManager::HandleKeyPressed(sf::Event KeyEvent)
{
	std::map<sf::Keyboard::Key, EventType> ControlMaps;
	
	//Define the control mappings. This is to make it easier to customize controls later. Also, I'd rather not deal with raw key events. 
	ControlMaps[sf::Keyboard::Up] = EventType::MOVE_UP;
	ControlMaps[sf::Keyboard::Down] = EventType::MOVE_DOWN;
	ControlMaps[sf::Keyboard::Left] = EventType::MOVE_LEFT;
	ControlMaps[sf::Keyboard::Right] = EventType::MOVE_RIGHT;

	return ControlMaps[KeyEvent.key.code];
}

void EventManager::HandleEvent(EventType Event)
{
	EventContextPair ContextPair = std::make_pair(CurrentContext, Event);
	std::vector<EventCallback> Callbacks = m_Callbacks[ContextPair];

	for (auto Callback : Callbacks)
		Callback(Event);
}

void EventManager::AddHook(const EventRange Range, const EventContext Context, EventCallback Callback)
{
	for (uint i = static_cast<uint>(Range.first); i <= static_cast<uint>(Range.second); ++i)
	{
		EventContextPair ContextPair = std::make_pair(Context, static_cast<EventType>(i));
		m_Callbacks[ContextPair].push_back(Callback);
	}
}

void EventManager::AddHook(const EventType Type, const EventContext Context, EventCallback Callback)
{
	EventContextPair ContextPair = std::make_pair(Context, Type);
	m_Callbacks[ContextPair].push_back(Callback);
}

