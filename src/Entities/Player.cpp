#include "Player.hpp"
#include "../Room.hpp"
#include "../fogpi/io.hpp"

void Player::Start(Vec2 _pos) {
    m_character = 'P';
    m_position = _pos;

    if (m_dice.empty())
        m_dice.push_back(Die{m_max_roll});
}

void Player::OpenChest()
{
    int reward = random_int(1, 15);
    m_gold += reward;
    printf("You got %d gold!\n", reward);

}

void Player::Update() {
    //while(request_char("hit w to continue: ") != 'w') {}

    char directionInput;

    do {
        directionInput = request_char("wasd and Enter to move");
    } while (directionInput != 'w' &&
             directionInput != 'a' &&
             directionInput != 's' &&
             directionInput != 'd');
    
    Vec2 direction(0.0f);

    switch (directionInput)
    {
    case 'w':
        direction = {0.0f, -1.0f};
        break;
    case 'a':
        direction = {-1.0f, 0.0f};
        break;
    case 's':
        direction = {0.0f, 1.0f};
        break;
    case 'd':
        direction = {1.0f, 0.0f};
        break;
    default:
        direction = {0.0f, 1.0f};
        break;
    }

    Vec2 tryPos = m_position + direction;

    if (room->GetLocation(tryPos) == 'K') {
        m_keyCount++;
        room->ClearLocation(tryPos);
    }

    if (room->GetLocation(tryPos) == 'C') {
        OpenChest();
        room->ClearLocation(tryPos);
    }

    if (room->GetLocation(tryPos) == ' ') {
        m_position = tryPos;
    }

    if (room->GetLocation(tryPos) == 'D' && room->enemyCount == 0) {
        room->OpenDoor(tryPos);
    }

    if(room->GetLocation(tryPos) == 'L' && m_keyCount >= 1 && room->enemyCount == 0) {
        m_keyCount--;
        room->OpenDoor(tryPos);
    }

    if (room->GetLocation(tryPos) == 'H') {
        room->FightHunter(tryPos);
    }

    if (room->GetLocation(tryPos) == 'B') {
        room->FightButcher(tryPos);
    }
}

void Player::Death(int gold, int strength) {
    printf("You died with %d gold and %d strength", gold, strength);
    char c = request_char(", press any button to end");
    std::exit(EXIT_SUCCESS);
}