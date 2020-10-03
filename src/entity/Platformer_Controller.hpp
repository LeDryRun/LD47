#ifndef TOWER_PLAYER_HPP
#define TOWER_PLAYER_HPP

#include "Tilemap_Entity.hpp";
#include "../audio/Noise_Maker.hpp"
class Mousey;
class Keyblade;
class UtilityMap;
class Gamepad;


class Platformer_Controller: public Tilemap_Entity, public Noise_Maker{
private:
	float gravity_acceleration=-0.8f;
	int speed=8;

	float falling_speed=0.0f;

	int jump_impulse=10;
	float jump_acceleration=0.2f;

	float terminal_velocity=-20.0f;

	bool grounded=false;
	bool jumping=false;

	bool wall_slide=false;

	bool facing_left=false;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
	Platformer_Controller();

	virtual void update(Tilemap&, Keyblade&, Gamepad&);
	virtual void load_animations(Imagehandler&) override;

};


#endif