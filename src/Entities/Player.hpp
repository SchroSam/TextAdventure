#pragma once

#include "../Dice.hpp"
#include "Entity.hpp"

class Player : public Entity
{
public:
    void Start(Vec2 _pos);
    void Update();

    int m_health = 20;
    int m_max_roll = 10;
    std::vector<Die> m_dice;

private:
    int m_keyCount = 0;
};