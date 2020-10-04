#include "Bullet.hpp"

void Bullet::update()
{
    if (returning)
    {
        // Get parent position
        Point home = Point(0, 0);

        Point target = get_center() - home;
        float distance = target.magnitude();

        if (distance < 0.1)
        {
            // Deal damage to enemy
            removing = true;
        }
        else
        {
            movement = target * 0.1;
            direction = target;
            move();

            movement = Point(0, 0);
        }
    }
}