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

    void Health::SetDeathHP(int DeathHP)
    {
        m_DeathHP = DeathHP;
    }

    int Health::GetHealth() const
    {
        return m_Health;
    }

    void Health::SetHealth(int Health)
    {
        m_Health = Health;
    }

    int Health::ReceiveDamage(int Damage)
    {
        if (m_Health - Damage < m_DeathHP)
            m_DeathCallback();
        else
            m_Health -= Damage;
        return m_Health;
    }

    Health::Health(std::function<void()> DeathCallback)
    {
        m_DeathHP = 0;
        m_Health = 100;

        m_DeathCallback = DeathCallback;
    }

    Health::~Health()
    {
    }
}
