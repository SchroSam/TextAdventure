#pragma once

#include <vector>
#include "Door.hpp"

class Entity;
class Player;
class Hunter;
class Monster;

class Room {
public:
    void Load(std::string _path);
    void Draw();
    void Update();
    char GetLocation(Vec2 _pos);
    void ClearLocation(Vec2 _pos);
    void OpenDoor(Vec2 _pos);
    void FightHunter(Vec2 _pos);
    void FightButcher(Vec2 _pos);
    int enemyCount;
private:
    std::vector<Entity*> m_entities;
    Player* m_player = nullptr;
    Hunter* m_hunter = nullptr;
    std::vector<Monster*> m_monsters;
    std::vector<std::vector<char>> m_map;
    std::vector<Door> m_doors;
    std::vector<std::string> colors = std::vector<std::string>();
};