#include "Entity.hpp"
#include "../image/Imagehandler.hpp"
#include <iostream>



void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const{
	target.draw(animations.at(current_animation_int).get_current_frame(), states);
}
void Entity::animate(){
	animations.at(current_animation_int).animate();
}

void Entity::create(Point p_p){
	hitbox.create(0,0,animations.at(0).get_frame_width(),animations.at(0).get_frame_height());
	set_position(p_p);
}


void Entity::create_hitbox(Point size_p, Point offset_p){
	hitbox_offset=offset_p;
	hitbox.create(position.get_x()+hitbox_offset.get_x(),position.get_y()+hitbox_offset.get_y(),size_p.get_x(),size_p.get_y());
}


void Entity::move(){
	position+=movement;
	for(int i=0;i<(int)animations.size();i++){
		animations.at(i).move(movement);
	}
	hitbox.move(movement);
}

void Entity::set_position(Point p_p){
	position=p_p;
	hitbox.set_position(position.get_x()+hitbox_offset.get_x(),position.get_y()+hitbox_offset.get_y());

	for(int i=0;i<(int)animations.size();i++){
		animations.at(i).set_position(position.get_x()+animations.at(0).get_frame_width()/2,position.get_y()+animations.at(0).get_frame_height()/2);
	}
}

void Entity::load_animations(Imagehandler& imagehandler){
	for(int i=0;i<(int)animations.size();i++){
		imagehandler.load_animation(animations.at(i));
	}
}