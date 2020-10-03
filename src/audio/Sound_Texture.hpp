#ifndef SOUND_TEXTURE_HPP
#define SOUND_TEXTURE_HPP


#include <SFML/Audio.hpp>
#include <string>
#include <iostream>

/*
	TBH this class is pretty pointless, it just has a sf::SoundBuffer and a name the program uses internally to refer to it
*/

class Sound_Texture{
private:
	sf::SoundBuffer buffer;
	std::string name;
public:
	Sound_Texture(std::string file_p, std::string name_p){
		if(!buffer.loadFromFile(file_p)){
			std::cout<<"Error loading file "<<file_p<<std::endl;
		}
		name=name_p;
	}

	sf::SoundBuffer& ref_buffer(){return buffer;}
	std::string get_name(){return name;}
};

#endif