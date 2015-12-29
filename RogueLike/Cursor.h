#pragma once
#include "Entity.h"
#include "Common.h"


class MovementSystem;
class EventManager;

class Cursor : public Entity
{

public:
	Cursor(const SpriteBlock sprite, MovementSystem& manager);
	~Cursor();
};

