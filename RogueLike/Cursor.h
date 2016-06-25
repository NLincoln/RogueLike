#pragma once
#include "Entity.h"

class MovementSystem;
class EventManager;

class Cursor : public Entity
{

public:
    Cursor(const SpriteList sprite, MovementSystem& manager);
    ~Cursor();
};

