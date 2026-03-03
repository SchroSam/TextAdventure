#include "Butcher.hpp"
#include "Player.hpp"
#include "../Dice.hpp"
#include <math.h>

void Butcher::Start(Vec2 _pos) {
    m_character = 'B';
    m_position = _pos;
    m_health = 8;
}

void Butcher::Update() {}

void Butcher::Fight(Player* m_player) 
{
    while (m_health > 0 && m_player->m_health > 0){
        printf("\n\n");
        RollStats player_stats = RollDice(m_player->m_dice);
        RollStats butcher_stats = RollDice(m_dice);
        printf("Player rolled %d using %zu, Butcher rolled %d using %zu, %d damage done to ", player_stats.total, m_player->m_dice.size(), butcher_stats.total, m_dice.size(), abs(player_stats.total-butcher_stats.total));
        if (player_stats.total > butcher_stats.total)
        {
            printf("Butcher\n");
            m_health -= (player_stats.total - butcher_stats.total);
        }
        else if (butcher_stats.total > player_stats.total)
        {
            printf("Player\n");
            m_player->m_health -= (butcher_stats.total - player_stats.total);
        }
        if (m_health < 0) m_health = 0;
        if (m_player->m_health < 0) m_player->m_health = 0;
        printf("Player Health: %d, Butcher Health: %d\n",m_player->m_health, m_health);
        if (m_player->m_health < 1 || m_health < 1) break;
        char p = request_char("Input w to keep fighting or s to retreat >> \n");
        if (p == 's') break;
    }
}