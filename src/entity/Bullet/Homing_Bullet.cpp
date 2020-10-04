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
	movement=direction*speed;
	Bullet::update();
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