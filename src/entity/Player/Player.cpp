#include "Player.hpp"

void Player::update(Point move, bool shifted)
{
    // Set movement based on vector
    movement = shifted ? move * i_PlayerSpd * 0.5f : move * i_PlayerSpd;

    // Keep player in screen
    Point next_p = get_center() + movement;
    if (next_p.get_x() < 16)
    {
        set_center(Point(16, next_p.get_y()));
        movement.set_x(0);
    }
    else if (next_p.get_x() > 1350)
    {
        set_center(Point(1350, next_p.get_y()));
        movement.set_x(0);
    }

    if (next_p.get_y() < 16)
    {
        set_center(Point(next_p.get_x(), 16));
        movement.set_y(0);
    }
    else if (next_p.get_y() > 752)
    {
        set_center(Point(next_p.get_x(), 752));
        movement.set_y(0);
    }

    // Move and reset movement vector
    Player::move();
    movement = Point(0,0);

    // Add points if looping
    if (b_isLooping)
    {
        if (f_LineLeft > 0 && get_center() != v_Line.back())
        {
            v_Line.push_back(get_center());
            f_LineLeft -= 0.01f;
        }
    }
}

void Player::start_loop()
{
    b_isLooping = true;

    f_LineLeft = f_LineLimit;
    v_Line.clear();
    v_Line.push_back(get_center());
}

void Player::validate_loop() 
{
    b_isLooping = false;

    // do_math

    v_Line.clear();
}