#ifndef NOISEMAKER_HPP
#define NOISEMAKER_HPP

class Audiohandler;
#include "Audiokey.hpp"
#include <string>
#include <vector>
#include <memory>

/*
	Defines a class that can request a sound to be played and manage that sounds once the request is accepted. Anything you want to make noise should inherit from this class

	add_sound needs to happen in the constructor of your child class, and load_sounds needs to happen in the constructor of your gamesate AFTER all desired sounds have been
	added. pretty much works just like animations in that sense. to request a sounds be played, just play_sound() with the EXACT name of the sound you want played. everything
	else works pretty much how you would expect.
	
	you do need to call set_state_of_origin after you've added all of the sounds, this should be the EXACT name of the gamestate that hold the instance, the audiohandler will use
	this data to pause the sound when that gamestate is no longer active. if you don't add the state name correctly the sound will just continue to play regardless of if the 
	state is currently active
*/

class Noise_Maker{
protected:
	std::vector<std::shared_ptr<Audiokey>> sounds;
	std::string state_of_origin="error";
public:
	Noise_Maker(){}
	virtual void load_sounds(Audiohandler&);
	virtual void play_sound(std::string);
	virtual void pause_sound(std::string);
	virtual void stop_sound(std::string);
	virtual void add_sound(std::string, sound_category::CATEGORY);
	virtual void loop_sound(std::string,bool);

	Audiokey get_key(std::string);//dont worry about it
	bool is_sound_playing(std::string);
	int get_sound_int(std::string);
	void set_state_of_origin(std::string soo_p){state_of_origin=soo_p;}

};

#endif