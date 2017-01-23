#pragma once
#include "Common.h"

//This will get filled out at a later date. For now, the important thing is to avoid compiler errors...
class Item
{
  //Because this is fleshing-out stage, all items will be a weapon that deals... 40 damage per hit
  uint m_Damage;

public:
  void SetDamage(uint Damage);
  uint GetDamage() const;

  Item();
  ~Item();
};

