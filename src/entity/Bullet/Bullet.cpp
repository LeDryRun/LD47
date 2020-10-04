#include "Bullet.hpp"

/*
void Bullet::update()
{
    if (returning)
    {
        // Get parent position
        Point home = sender->get_center();

        Point target = get_center() - home;
        float distance = target.magnitude();

        if (distance < 0.05)
        {
            sender->take_damage(damage);
            removing = true;
        }
        else
        {
            movement = target * 0.1f;
            direction = target;
            move();

            movement = Point(0, 0);
        }
    }
}
*/