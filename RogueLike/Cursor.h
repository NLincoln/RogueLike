#pragma once
#include "Entity.h"
#include "Common.h"


class EntityManager;
class EventManager;

class Cursor : public Entity
{

public:
	Cursor(const SpriteBlock sprite, EntityManager& manager);
	~Cursor();
};

