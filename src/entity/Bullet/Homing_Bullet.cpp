#include "Homing_Bullet.hpp"
#include "../../communal/Communal.hpp"
#include <math.h>
#include <iostream>

Homing_Bullet::Homing_Bullet(){
	animations.push_back(Animation("bullet_flying1"));
	animations.push_back(Animation("bullet_burst1"));
	animations.at(1).set_looping(false);
	damage=5;
	speed=5;
	radius=5;
}

void Homing_Bullet::update(){
	if(exploding){
		current_animation_int=1;
		if(animations.at(1).is_finished()){
			removing=true;
		}
		animate();
    }
    else if (returning)
    {
        movement = Point(0, -5);
        move();

        /*
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
        */
    }
    else
    {
		move();
	}
}

void Homing_Bullet::create(Point center_p, int radius_p, Point direction_p){
	int degrees=90;
	set_center(center_p);
	hitbox.create(center_p,radius_p);

	direction=direction_p;
	direction.normalize();
	degrees=atan2_degrees(direction.get_y(),(direction.get_x()))+180;
	movement=direction*speed;
	rotate_animations(degrees);

}



Homing_Bullet Homing_Bullet::create_copy(Point center_p, int radius_p, Point direction_p, Enemy* sender){
	create(center_p,radius_p,direction_p);
	this->sender = sender;
	return *this;
}

Homing_Bullet Homing_Bullet::create_copy(Bullet_Blueprint b_p){
	create(b_p.center,radius,b_p.direction);
	this->sender = b_p.sender_;
	return *this;
}