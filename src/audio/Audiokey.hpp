#ifndef AUDIOKEY_HPP
#define AUDIOKEY_HPP

#include <string>
#include <SFML/Audio.hpp>
class Audiohandler;

/*
	Seriously, don't worry about it. just look at Noisemaker and Audiohandler
*/


namespace sound_category{
	enum CATEGORY{
		OTHER=0,
		SFX=1,
		DIALOGUE=2
	};
};


class Audiokey{
public:
	private:
		bool maker_valid=true;
		bool handler_valid=false;
		std::string name;
		sound_category::CATEGORY category;
		std::string state_of_origin;
		bool looping=false;

		bool is_playing=false;

		sf::Sound sound;
		friend class Audiohandler;
	public:
		Audiokey(){};
		Audiokey(std::string name_p,sound_category::CATEGORY c_p){
			name=name_p;
			category=c_p;
		}

		void set_maker_valid(bool b_p){maker_valid=b_p;}
		void set_name(std::string name_p){name=name_p;}
		void set_category(sound_category::CATEGORY cat_p){category=cat_p;}
		void set_state_of_origin(std::string o_p){state_of_origin=o_p;}
		void set_looping(bool l_p){looping=l_p;sound.setLoop(l_p);}
		void set_position(int x_p, int y_p, int z_p){sound.setPosition(x_p,y_p,z_p);}

		bool is_maker_valid(){return maker_valid;}
		bool is_handler_valid(){return handler_valid;}
		std::string get_name(){return name;}
		sound_category::CATEGORY get_category(){return category;}
		std::string get_state_of_origin(){return state_of_origin;}
		bool is_looping(){return looping;}
		bool is_it_playing(){return is_playing;}

		void pause_sound(){sound.pause();is_playing=false;}
		void stop_sound(){sound.stop();is_playing=false;}

		void set_buffer(sf::SoundBuffer& buffer){
			sound.setBuffer(buffer);
			//std::cout<<name<<" buffer set!"<<std::endl;
		}
};


#endif