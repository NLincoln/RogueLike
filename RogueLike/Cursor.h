#pragma once
#include "Entity.h"
#include "Common.h"


class EventManager;

class Cursor : public Entity
{

public:
	Cursor(const SpriteBlock sprite, EventManager& manager);
	~Cursor();
};

