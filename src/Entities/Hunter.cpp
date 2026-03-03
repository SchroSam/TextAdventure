#include "Hunter.hpp"
#include "Player.hpp"
#include "../Dice.hpp"
#include <math.h>

void Hunter::Start(Vec2 _pos) {
    m_character = 'H';
    m_position = _pos;
    m_health = 8;
}

void Hunter::Update() {}

void Hunter::Fight(Player* m_player) 
{
    while (m_health > 0 && m_player->m_health > 0){
        printf("\n\n");
        RollStats player_stats = RollDice(m_player->m_dice);
        RollStats hunter_stats = RollDice(m_dice);
        printf("Player rolled %d using %zu, Hunter rolled %d using %zu, %d damage done to ", player_stats.total, m_player->m_dice.size(), hunter_stats.total, m_dice.size(), abs(player_stats.total-hunter_stats.total));
        if (player_stats.total > hunter_stats.total)
        {
            printf("Hunter\n");
            m_health -= (player_stats.total - hunter_stats.total);
        }
        else if (hunter_stats.total > player_stats.total)
        {
            printf("Player\n");
            m_player->m_health -= (hunter_stats.total - player_stats.total);
        }
        if (m_health < 0) m_health = 0;
        if (m_player->m_health < 0) m_player->m_health = 0;
        printf("Player Health: %d, Hunter Health: %d\n",m_player->m_health, m_health);
        if (m_player->m_health < 1 || m_health < 1) break;
        char p = request_char("Input w to keep fighting or s to retreat >> \n");
        if (p == 's') break;
    }
}