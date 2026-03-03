#include "Room.hpp"

#include "Entities/Player.hpp"
#include "Entities/Hunter.hpp"
#include "Entities/Butcher.hpp"

#include <fstream>
#include <string>

void Room::Load(std::string _path)
{
    enemyCount = 0;
    m_map.clear();
    m_doors.clear();

    std::ifstream file;
    file.open(_path);

    if (!file.is_open())
    {
        printf("file not found at: %s \n", _path.c_str());
        exit(1);
    }

    std::string word;
    int number;

    while (file >> word)
    {
        if (word == "level")
        {
            if (file >> number)
            {
                printf("open level: %i\n", number);
            }
        }

        if (word == "next_level")
        {
            if (file >> word)
            {
                m_doors.push_back(Door());
                m_doors[m_doors.size() - 1].path = word;
            }
        }

        if (word == "map")
        {
            m_map.push_back(std::vector<char>());
            while(file >> word)
            {
                if (word == "-2")
                {
                    break;
                }

                if (word == "-1")
                {
                    m_map.push_back(std::vector<char>());
                    continue;
                }

                if (word == "0")
                    m_map[m_map.size() - 1].push_back(' ');
                
                else
                    m_map[m_map.size() - 1].push_back(word[0]);
                
            }
        }
    }

    int doorCount = 0;
    int entityCount = 0;
    for (int y = 0; y < m_map.size(); y++)
    {
        for (int x = 0; x < m_map[y].size(); x++)
        {
            if (m_map[y][x] == 'S')
            {
                if (m_player == nullptr)
                    m_player = new Player();
                
                m_player->Start(Vec2(x,y));
                m_map[y][x] = ' ';
            }

            if (m_map[y][x] == 'D' || m_map[y][x] == 'L')
            {
                if (m_doors.size() - 1 >= doorCount)
                {
                    m_doors[doorCount].pos.x = x;
                    m_doors[doorCount].pos.y = y;
                    doorCount++;
                }
            }

            if (m_map[y][x] == 'H')
            {
                Hunter* h = new Hunter;
                h->Start(Vec2(x,y));
                m_entities.push_back(h);
                entityCount++;
                enemyCount++;
            }

            if (m_map[y][x] == 'B')
            {
                Butcher* b = new Butcher;
                b->Start(Vec2(x,y));
                m_entities.push_back(b);
                entityCount++;
                enemyCount++;
            }

        }
    }

    //printf("enemy count: %d\n", enemyCount);
}

void Room::Update()
{
    Draw();
    if (m_player != nullptr)
    {
        m_player->room = this;
        m_player->Update();
    }
}

void Room::Draw()
{
    for (int y = 0; y < m_map.size(); y++)
    {
        for (int x = 0; x < m_map[y].size(); x++)
        {
            printf("%c ", GetLocation(Vec2(x, y)));
        }
        printf("\n");
    }
}

char Room::GetLocation(Vec2 _pos)
{
    if (_pos.y >= m_map.size())
        return ' ';
    
    if (_pos.x >= m_map[_pos.y].size())
        return ' ';

    if (m_player != nullptr)
        if (m_player->GetPosition() == _pos)
            return m_player->Draw();
    
    return m_map[_pos.y][_pos.x];
}

void Room::ClearLocation(Vec2 _pos)
{
    if (_pos.y >= m_map.size())
        return;
    
    if (_pos.x >= m_map[_pos.y].size())
        return;
    
    m_map[_pos.y][_pos.x] = ' ';
}

void Room::OpenDoor(Vec2 _pos)
{
    for(int i = 0; i < m_doors.size(); i++)
    {
        if (m_doors[i].pos == _pos)
        {
            // Healing
            if(random_int(0, 2) != 0)
            {
                int healAmount = random_int(1, 5);
                m_player->m_health += healAmount;
                printf("You healed %d health!\n", healAmount);
            }

            if(m_doors[i].path != "assets/level_3.map" || random_int(0, 1)) // non-zero is true
                Load(m_doors[i].path.c_str());
            else
                Load("assets/level_3-C.map");
        }
    }
}

void Room::FightHunter(Vec2 _pos)
{
    for (int i = 0; i < m_entities.size(); i++)
    {
        if (m_entities[i])
        {
            Hunter* h = dynamic_cast<Hunter*>(m_entities[i]);
            if (h)
                h->Fight(m_player);
                auto it = m_entities.begin() + i;
                if (m_player->m_health > 0) {
                    m_entities.erase(it);
                    Room::ClearLocation(_pos);
                    m_player->m_gold += 5;
                    enemyCount--;
                }
                else if (m_player->m_health < 1) m_player->Death(m_player->m_gold);
        }
    }
}

void Room::FightButcher(Vec2 _pos)
{
    for (int i = 0; i < m_entities.size(); i++)
    {
        if (m_entities[i])
        {
            Butcher* h = dynamic_cast<Butcher*>(m_entities[i]);
            if (h)
                h->Fight(m_player);
                auto it = m_entities.begin() + i;
                if (m_player->m_health > 0 && h->m_health < 1) {
                    m_entities.erase(it);
                    Room::ClearLocation(_pos);
                    m_player->m_gold += 10;
                    enemyCount--;
                }
                else if (m_player->m_health < 1) m_player->Death(m_player->m_gold);
                printf("\n\n\n---FIGHT OVER---\nHealth: %d\nGold: %d\nStrength: %d\n", m_player->m_health, m_player->m_gold, m_player->m_dice[0].sides);
        }
    }
}