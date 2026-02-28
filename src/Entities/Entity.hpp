#pragma once

#include "../fogpi/Math.hpp"

class Room;

class Entity {
    public:
        Room* room;

        virtual void Start(Vec2 _pos) {}
        virtual void Update() {}

        Vec2 GetPosition() { return m_position; };
        char Draw() { return m_character; }

        Vec2 m_position;

    protected:
        char m_character;
};