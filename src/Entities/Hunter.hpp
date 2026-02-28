#pragma once

#include "Entity.hpp"
#include "Player.hpp"
#include "../Room.hpp"
#include "../Dice.hpp"
#include "../fogpi/io.hpp"

class Hunter : public Entity
{
public:
    void Start(Vec2 _pos);
    void Update();
    void Fight(Player* m_player);
    int m_health = 10;
    int m_max_roll = 5;
    std::vector<Die> m_dice;
private:
};