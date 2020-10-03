#include "gamestate/Window_Manager.hpp"
#include "communal/Communal.hpp"

int main(){
	Window_Manager window_manager;
	while (window_manager.is_open()){
		window_manager.update();
	}
	Duration_Check::print_breakpoints();
	return 0;
}
