#pragma once
#include <functional>


class ObstructionComponent
{
	int m_Strength;
	std::function<void()> m_DestroyedCallback;
public:
	int GetStrength() const { return m_Strength; }
	void SetStrength(int Strength);
	int DealDamage(int Damage);

	ObstructionComponent(std::function<void()> DestroyedCallback);
	~ObstructionComponent();
};

