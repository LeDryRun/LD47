#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "../Circular_Entity.hpp"

class Player : public Circular_Entity
{
    private:
        float i_PlayerSpd = 10.f;

        std::vector<Point> v_Line;
        float f_LineLimit = 1.0f;
        float f_LineLeft = f_LineLimit;
        bool b_isLooping = false;
    public:
        Player() { animations.push_back(Animation("green_circle")); };

        float get_PlayerSpd() { return i_PlayerSpd; };
        void set_PlayerSpd(int i) { i_PlayerSpd = i; };
        std::vector<Point> get_Line() { return v_Line; };
        float get_LineLimit() { return f_LineLimit; };
        void set_LineLimit(float f) { f_LineLimit = f; };
        float get_LineLeft() { return f_LineLeft; };
        void set_LineLeft(float f) { f_LineLeft = f; };
        bool get_isLooping() { return b_isLooping; };
        void set_isLooping(bool b) { b_isLooping = b; };

        void update(Point move, bool shifted);
        void start_loop();
        void validate_loop();
};

#endif