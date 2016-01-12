#pragma once
#include <vector>
#include "Entity.h"
#include "Enemy.h"
#include "Event.h"

class Player;
class MovementSystem;


class EnemyManager
{
	std::map<EventType, std::vector<EventCallback>> m_EnemyCallbacks;
	std::vector<Enemy*> m_Entities;

public:
	void AddHook(EventType Type, EventCallback Callback);
	void AddHook(EventRange Range, EventCallback Callback);

	void AddEntity(Enemy* NewEntity);

    EnemyManager(EventManager& EventManager, MovementSystem& MovementSystem, Player* p);
	~EnemyManager();
};

/*
* All enemies are the same code: the only difference is in the weapons that they carry.
* Unfortunately, there is no concept of a weapon or inventory at this point. 
*/