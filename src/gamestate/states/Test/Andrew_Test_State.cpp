#include "Andrew_Test_State.hpp"
#include "../../../communal/Communal.hpp"



Andrew_Test_State::Andrew_Test_State(Imagehandler& imagehandler,Audiohandler& audiohandler):test_layer("test_layer"){
	state_name="andrew_test_state";

	if (!m_debug_font.loadFromFile("../assets/font/System_Breach_wide.ttf"))
	{
		std::cout << "Error Loading Font!";
	}

	m_debug_text.setFont(m_debug_font);

	m_bullet_manager = Bullet_Manager();
	m_test_enemy = Enemy_Straight(&m_bullet_manager, &m_test_player);
	m_test_burst_enemy = Enemy_Burst(&m_bullet_manager);

	load_sprites(imagehandler);

	m_test_enemy.create(Point(200, 200), 16);
	m_test_burst_enemy.create(Point(200, 100), 16);
	m_test_player.create(Point(500, 500), 16);
}

void Andrew_Test_State::load_sprites(Imagehandler& imagehandler){
	m_bullet_manager.load_animations(imagehandler);
	m_test_enemy.load_animations(imagehandler);
	m_test_burst_enemy.load_animations(imagehandler);
	m_test_player.load_animations(imagehandler);
}

void Andrew_Test_State::update_layer_resolutions(){
	Gamestate::update_layer_resolutions();
	test_layer.resolve_new_resolution();
}

void Andrew_Test_State::update(Mousey& mouse,Keyblade& keyboard,Gamepad& gamepad){Duration_Check::start("-Platformer update");
	Gamestate::update_gui_layer(mouse,keyboard,gamepad);

	mouse.set_layer(test_layer);

	check_gamepad(gamepad);
	check_keyboard(keyboard);
	float v_hor = keyboard.get_key('d').is_pressed() - keyboard.get_key('a').is_pressed();
	v_hor = fabs(gamepad.get_left_stick_x()) > 0 ? gamepad.get_left_stick_x() / 100.f : v_hor;
	float v_vert = keyboard.get_key('s').is_pressed() - keyboard.get_key('w').is_pressed();
	v_vert = fabs(gamepad.get_left_stick_y()) > 0 ? gamepad.get_left_stick_y() / 100.f : v_vert;

	m_test_player.update(Point(v_hor, v_vert), keyboard.get_key('v').is_pressed() || gamepad.is_pressed(GAMEPAD_X));

	if (keyboard.get_key('b').is_pressed() || gamepad.is_pressed(GAMEPAD_A))
	{
		if (!m_test_player.get_isLooping())
			m_test_player.start_loop();
	}
	else
	{
		if (m_test_player.get_isLooping())
			m_test_player.validate_loop();
	}

	m_test_enemy.update();
	m_test_burst_enemy.update();

	Bullet_Vector bullets_hitting_player = m_bullet_manager.bullets_colliding_with_hitbox(m_test_player.get_hitbox());
	for (int i = 0; i < (int)bullets_hitting_player.size(); i++) {
		bullets_hitting_player.at(i)->set_exploding(true);
	}
	m_bullet_manager.update();

	int bulletx = 0;
	int bullety = 0;

	if (m_bullet_manager.getLiveBullets().size() > 0) {
		bulletx = m_test_burst_enemy.getCurrentAnimation().get_current_frame().getRotation();
		bullety = m_bullet_manager.getLiveBullets().at(0)->get_center().get_y();
	}

	m_debug_text.setString("Enemy Rotation: " + std::to_string(bulletx));
	m_debug_text.setCharacterSize(12);
	m_debug_text.setFillColor(sf::Color::White);

	/*
		UPDATE TOP LAYER AND DESCEND, RENDER BOTTOM LAYER AND ASCEND

		ALWAYS SET MOUSE TO BACKGROUND LAYER LAST
	*/

	mouse.set_layer(background_layer);
Duration_Check::stop("-Platformer update");}

void Andrew_Test_State::render(sf::RenderWindow& window){Duration_Check::start("-Platformer render");

	Gamestate::render_background_layer(window);
	window.setView(test_layer);
	window.draw(m_test_enemy);
	window.draw(m_test_burst_enemy);
	window.draw(m_debug_text);

	sf::VertexArray points(sf::LinesStrip, 0);
	for (Point p : m_test_player.get_Line()) {
		points.append(sf::Vertex(sf::Vector2f(p.get_x(), p.get_y()), sf::Color::White));
	}

	window.draw(points);
	window.draw(m_test_player);
	window.draw(m_bullet_manager);


	Gamestate::render_gui_layer(window);
Duration_Check::stop("-Platformer render");}


void Andrew_Test_State::execute_data(Data_Packet data_p){

}
void Andrew_Test_State::check_keyboard(Keyblade& keyboard){
	if(keyboard.get_key('E').was_just_pressed()){
		send_data.push_back(Data_Packet("set_state",MANAGER,{"pause_menu"}));
	}
}
void Andrew_Test_State::check_gamepad(Gamepad& gamepad){
	if(gamepad.was_just_pressed(GAMEPAD_START)){
		send_data.push_back(Data_Packet("set_state",MANAGER,{"pause_menu"}));
	}
/*
	if(gamepad.was_just_pressed(GAMEPAD_A)){

	}

	if(gamepad.get_left_stick_y()>0){

	}else if(gamepad.get_left_stick_y()<0 ){
		;
	}else if(gamepad.get_left_stick_x()<0 ){

	}else if(gamepad.get_left_stick_x()>0 ){

	}*/
}