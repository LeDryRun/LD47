#ifndef ATEST_STATE_HPP
#define ATEST_STATE_HPP

#include "../../Gamestate.hpp"
#include "../../../tilemap/Tilemap.hpp"
#include "../../../audio/Audiohandler.hpp"
#include "../../../entity/Platformer_Controller.hpp"
#include "../../../entity/enemy/Enemy_Straight.hpp"
#include "../../../entity/enemy/Enemy_Burst.hpp"
#include "../../../entity/Bullet/Bullet_Manager.hpp"
#include "../../../wave/Wave_Manager.hpp"

class Andrew_Test_State:public Gamestate{
private:

	Layer test_layer;

	Bullet_Manager m_bullet_manager;
	Wave_Manager m_wave_manager;
	Wave m_wave_one;
	Wave m_wave_two;
	Player m_test_player;
    World_Data world;

	sf::Font m_debug_font;
	sf::Text m_debug_text;

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