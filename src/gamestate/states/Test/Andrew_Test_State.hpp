#ifndef ATEST_STATE_HPP
#define ATEST_STATE_HPP

#include "../../Gamestate.hpp"
#include "../../../tilemap/Tilemap.hpp"
#include "../../../audio/Audiohandler.hpp"
#include "../../../entity/Platformer_Controller.hpp"
class Andrew_Test_State:public Gamestate{
private:

	Layer test_layer;

public:
	Andrew_Test_State(Imagehandler& imagehandler,Audiohandler& audiohandler);
	~Andrew_Test_State(){}
	void load_sprites(Imagehandler& imagehandler)override;
	void update_layer_resolutions()override;
	void update(Mousey&,Keyblade&,Gamepad&)override;
	void render(sf::RenderWindow& window)override;
	void execute_data(Data_Packet)override;
	void check_keyboard(Keyblade&);
	void check_gamepad(Gamepad&);


};


#endif