#include "Noise_Maker.hpp"
#include "Audiohandler.hpp"

void Noise_Maker::load_sounds(Audiohandler& audiohandler){
	for(int i=0;i<(int)sounds.size();i++){
		audiohandler.load_audiokey(*sounds.at(i));
		sounds.at(i)->set_state_of_origin(state_of_origin);
	}
}

void Noise_Maker::play_sound(std::string name_p){
	for(int i=0;i<(int)sounds.size();i++){
		if(sounds.at(i)->get_name()==name_p){
			Audiohandler::add_sound_request(sounds.at(i));
			//std::cout<<"requesting sound "<<name_p<<std::endl;
			return;
		}
	}
}
void Noise_Maker::pause_sound(std::string name_p){
	for(int i=0;i<(int)sounds.size();i++){
		if(sounds.at(i)->get_name()==name_p){
			sounds.at(i)->pause_sound();
			return;
		}
	}
}
void Noise_Maker::stop_sound(std::string name_p){
	for(int i=0;i<(int)sounds.size();i++){
		if(sounds.at(i)->get_name()==name_p){
			sounds.at(i)->stop_sound();
			return;
		}
	}
}
void Noise_Maker::add_sound(std::string name_p,sound_category::CATEGORY c_p){
	sounds.push_back(std::make_shared<Audiokey>(name_p,c_p));
}
void Noise_Maker::loop_sound(std::string name_p,bool loop_p){
	for(int i=0;i<(int)sounds.size();i++){
		if(sounds.at(i)->get_name()==name_p){
			sounds.at(i)->set_looping(loop_p);
			return;
		}
	}
}
int Noise_Maker::get_sound_int(std::string name_p){
	for(int i=0;i<(int)sounds.size();i++){
		if(sounds.at(i)->get_name()==name_p){
			return i;
		}
	}
	return -1;
}
Audiokey Noise_Maker::get_key(std::string name_p){
	for(int i=0;i<(int)sounds.size();i++){
		if(sounds.at(i)->get_name()==name_p){
			return *sounds.at(i);
		}
	}
	std::cout<<"unable to find key named "<<name_p<<std::endl;
	return Audiokey();
}
bool Noise_Maker::is_sound_playing(std::string name_p){
	for(int i=0;i<(int)sounds.size();i++){
		if(sounds.at(i)->get_name()==name_p){
			return sounds.at(i)->is_it_playing();
		}
	}
	std::cout<<"unable to find sound named "<<name_p<<std::endl;
	return false;
}