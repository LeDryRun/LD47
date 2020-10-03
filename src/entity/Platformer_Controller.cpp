#include "Platformer_Controller.hpp"
#include "../input/Mousey.hpp"
#include "../input/Keyblade.hpp"
#include "../input/Gamepad.hpp"
#include "../image/Imagehandler.hpp"
#include "../tilemap/Tilemap.hpp" 
#include <math.h>


Platformer_Controller::Platformer_Controller(){
	set_state_of_origin("platformer_state");
	gravity_acceleration=-0.6f;
	jump_impulse=8;
	jump_acceleration=0.4f;
	terminal_velocity=-10.0f;
	speed=4;
}

void Platformer_Controller::draw(sf::RenderTarget& target, sf::RenderStates states) const{
	target.draw(animations.at(current_animation_int).get_current_frame(), states);
}

void Platformer_Controller::load_animations(Imagehandler& imagehandler){
	animations.push_back(Animation("Player_Idle"));
	animations.push_back(Animation("Player_Run"));
	animations.push_back(Animation("Player_Jump"));
	animations.push_back(Animation("Player_Wall_Slide"));
	for(int i=0;i<(int)animations.size();i++){
		imagehandler.load_animation(animations.at(i));
	}
}


void Platformer_Controller::update(Tilemap&  tilemap, Keyblade& keyboard, Gamepad& gamepad){


	movement=Point(0,0);
	Point dir=Point(0,0);

	wall_slide=false;
	if(keyboard.get_key('a').is_pressed() || gamepad.get_left_stick_x()<0 ){
		//std::cout<<"a"<<std::endl;
		dir=Cardinal::West;
		movement=movement+(dir*speed);
		if(check_tilemap_collision(tilemap)){
			wall_slide=true;
		}
		if(!wall_slide){
			facing_left=true;
		}
	}
	if(keyboard.get_key('d').is_pressed() || gamepad.get_left_stick_x()>0 ){
		//std::cout<<"d"<<std::endl;
		dir=Cardinal::East;
		movement=movement+(dir*speed);
		if(check_tilemap_collision(tilemap)){
			wall_slide=true;
		}
		if(!wall_slide){
			facing_left=false;
		}
	}
	for(int i=0;i<(int)animations.size();i++){
		animations.at(i).set_h_mirror(facing_left);
	}


	if(wall_slide && falling_speed<=0){
		falling_speed+=gravity_acceleration/4;
	}else{
		falling_speed+=gravity_acceleration;
	}

	if(falling_speed<terminal_velocity){
		falling_speed=terminal_velocity;
	}

	if(falling_speed<10*jump_acceleration){
		jumping=false;
	}

	if(keyboard.get_key(' ').is_pressed() || gamepad.is_pressed(GAMEPAD_A)){
		if(grounded){
			falling_speed+=jump_impulse;
			jumping=true;
			grounded=false;
			current_animation_int=2;
		}else if(jumping){
			falling_speed+=jump_acceleration;
		}
	}else{
		jumping=false;
	}
	if(grounded){
		if(animations.at(current_animation_int).is_looping()==true){
			if(movement.get_x()!=0){
				current_animation_int=1;
			}else{
				current_animation_int=0;
			}
		}
	}else{
		if(wall_slide){
			current_animation_int=3;
		}else{
			current_animation_int=2;
		}
	}


	movement=movement+(Point(Cardinal::North)*falling_speed);

	tilemap_collide_physics(tilemap);
	move();

	movement=Point(0,1);
	if(check_tilemap_collision(tilemap)){
		falling_speed=0;
		grounded=true;
	}else{
		grounded=false;
	}
	movement=Point(0,-1);
	if(check_tilemap_collision(tilemap)){
		if(falling_speed>0){
			falling_speed=0;
		}
		jumping=false;
	}
	animate();

}