#include "Item.h"


void Item::SetDamage(uint Damage)
{
	m_Damage = Damage;
}

uint Item::GetDamage() const
{
	return m_Damage;
}

Item::Item()
{
}


Item::~Item()
{
}
