#ifndef WINDOW_MANAGER_HPP
#define WINDOW_MANAGER_HPP
#include "Gamestate_Manager.hpp"

class Window_Manager{
private:

	static int execution_fps;
	chrono::milliseconds sleep_time;

	int incorrect_window_size_counter=0;
	int iws_counter_max=30;
	sf::RenderWindow window;
	sf::VideoMode videomode;
	bool open=true;
	bool resolution_error=false;

	Gamestate_Manager gamestate_manager;
public:
	Window_Manager();

	void recieve_data(Data_Packet data);
	void update();

	bool is_open(){return open;}

	static int get_execution_fps(){return execution_fps;}
	void set_execution_fps(int _i_p);
};

#endif