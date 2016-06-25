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

    class Health
    {
        int m_Health;
        int m_DeathHP;
        std::function<void()> m_DeathCallback;
    public:
        void SetDeathHP(int DeathHP);

        int GetHealth() const;
        void SetHealth(int Health);
        int ReceiveDamage(int Damage);

        Health(std::function<void()> DeathCallback);
        ~Health();
    };

}
