#ifndef GAMEPLAY_STATE_HPP
#define GAMEPLAY_STATE_HPP

#include "../Gamestate.hpp"
#include "../../tilemap/Tilemap.hpp"
#include "../../audio/Audiohandler.hpp"
#include "../../entity/Platformer_Controller.hpp"

class Gameplay_State:public Gamestate{
private:

	Layer test_layer;

	Tilemap platform_map;

	Platformer_Controller player;

public:
	Gameplay_State(Imagehandler& imagehandler,Audiohandler& audiohandler);
	~Gameplay_State(){}
	void load_sprites(Imagehandler& imagehandler)override;
	void update_layer_resolutions()override;
	void update(Mousey&,Keyblade&,Gamepad&)override;
	void render(sf::RenderWindow& window)override;
	void execute_data(Data_Packet)override;
	void check_keyboard(Keyblade&);
	void check_gamepad(Gamepad&);


};


#endif