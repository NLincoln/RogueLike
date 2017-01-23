#include "DamageSystem.h"
#include "Item.h"
#include "Entity.h"

//Sometimes a simpler solution is best: remember to always consider the necessity of a full class

uint CalculateDamage(const Item& Item, Entity* Victim) 
{
	uint Damage = 0;
	Damage += Item.GetDamage();
	
	return Damage;
}