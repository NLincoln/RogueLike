#include "ObstructionComponent.h"


void ObstructionComponent::SetStrength(int Strength)
{
	m_Strength = Strength;
}

int ObstructionComponent::DealDamage(int Damage)
{
	m_Strength -= Damage;
	
	if (m_Strength <= 0)
		m_DestroyedCallback();

	return m_Strength;
}

ObstructionComponent::ObstructionComponent(std::function<void()> DestroyedCallback): m_Strength(0)
{
	m_DestroyedCallback = DestroyedCallback;
}


ObstructionComponent::~ObstructionComponent()
{
}
