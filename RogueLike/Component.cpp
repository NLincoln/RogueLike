#include "Component.h"
namespace Comp
{

	void Obstruction::SetStrength(int Strength)
	{
		m_Strength = Strength;
	}

	int Obstruction::DealDamage(int Damage)
	{
		m_Strength -= Damage;

		if (m_Strength <= 0)
			m_DestroyedCallback();

		return m_Strength;
	}

	Obstruction::Obstruction(std::function<void()> DestroyedCallback) : m_Strength(0)
	{
		m_DestroyedCallback = DestroyedCallback;
	}

	Obstruction::~Obstruction()
	{
	}
}
