#include "Hunter.hpp"
#include "Player.hpp"
#include "../Dice.hpp"
#include <math.h>

void Hunter::Start(Vec2 _pos) {
    m_character = 'H';
    m_position = _pos;
    m_health = 10;
    m_dice.push_back(Die{5});
}

void Hunter::Update() {}

void Hunter::Fight(Player* m_player) 
{
    RollStats player_stats = RollDice(m_player->m_dice);
    RollStats hunter_stats = RollDice(m_dice);
    printf("Player rolled %d, Hunter rolled %d, %d damage done to ", player_stats.total, hunter_stats.total, abs(player_stats.total-hunter_stats.total));
    if (player_stats.total > hunter_stats.total)
    {
        m_health -= (player_stats.total - hunter_stats.total);
    }
    else if (hunter_stats.total > player_stats.total)
    {
        m_player->m_health -= (hunter_stats.total - player_stats.total);
    }
}