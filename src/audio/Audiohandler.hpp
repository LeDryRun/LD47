#ifndef AUDIOHANDLER_HPP
#define AUDIOHANDLER_HPP

#include "Audiokey.hpp"
#include <memory>
#include <vector>
#include "Sound_Texture.hpp"

/*
	This one's a lot.

	Essentially all sounds are split into categories, and each category has an associated array with limited space to hold the sounds.

	Because of the way sound data is saved by SFML, a Noisemaker will send some data as a request to this class to create a new sound instance.
	Don't worry about the intricacies of this.

	To add a new sound into the game you call add_buffer (a buffer is to a sound as a Texture is to a sprite) and give it a filepath to the wav file 
	as well as a name to be used internally. The Noisemaker will need to ask for this name exactly in order for the sound to be played. add new bufffers in the Audiohandler constructor
*/

class Audiohandler{
private:

	static std::shared_ptr<Audiokey> other_player[];
	static const int other_size;
	static float other_volume;
	static void request_other(std::shared_ptr<Audiokey>);

	static std::shared_ptr<Audiokey> sfx_player[];
	static const int sfx_size;
	static float sfx_volume;
	static void request_sfx(std::shared_ptr<Audiokey>);

	static std::shared_ptr<Audiokey> dialogue_player[];
	static const int dialogue_size;
	static float dialogue_volume;
	static void request_dialogue(std::shared_ptr<Audiokey>);
	
	static bool volume_update;

	float global_volume_scale=1.0f;
	float music_volume=100.0f;
	sf::Music background_music;

	std::string current_state;

	std::vector<std::shared_ptr<Audiokey>> paused_by_manager;

	std::vector<std::unique_ptr<Sound_Texture>> buffers;

	sf::SoundBuffer error_sound;

public:
	Audiohandler(){load();};
	void load();
	void load_audiokey(Audiokey&);
	void add_buffer(std::string,std::string);
	void set_background_music(std::string);
	void update();
	void change_gamestate(std::string);

	static void instantiate_player();
	static void add_sound_request(std::shared_ptr<Audiokey>);
	static void set_volume(float, sound_category::CATEGORY);
};

#endif