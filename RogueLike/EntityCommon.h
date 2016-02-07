#pragma once
#include "Event.h"
#include "World.h"

enum class direction
{
	North = 0, South, East, West
};

inline WorldPos Move(WorldPos CurrentPos, direction dir, uint magnitude = 1) 
{
	switch (dir)
	{
	case direction::North: CurrentPos.y -= magnitude; break;
	case direction::South: CurrentPos.y += magnitude; break;
	case direction::East:  CurrentPos.x += magnitude; break;
	case direction::West:  CurrentPos.x -= magnitude; break;
	default: break;
	}
	return CurrentPos;
}

inline WorldPos Move(WorldPos CurrentPos, EventType Type, uint magnitude)
{
	direction dir = direction::North;
	switch (Type)
	{
	case EventType::MOVE_LEFT:  dir = direction::West; break;
	case EventType::MOVE_RIGHT: dir = direction::East; break;
	case EventType::MOVE_UP:    dir = direction::North; break;
	case EventType::MOVE_DOWN:  dir = direction::South; break;
	default: break;
	}
	return Move(CurrentPos, dir, magnitude);
}
