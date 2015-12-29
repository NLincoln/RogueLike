#pragma once
#include <functional>

namespace Comp
{
	class Obstruction
	{
		int m_Strength;
		std::function<void()> m_DestroyedCallback;
	public:
		int GetStrength() const { return m_Strength; }
		void SetStrength(int Strength);
		int DealDamage(int Damage);

		Obstruction(std::function<void()> DestroyedCallback);
		~Obstruction();
	};
}
