#ifndef TILESET_HPP
#define TILESET_HPP

#include <string>
#include <vector>

/*
	This class holds info about a particular png file designed to be used as a set of tiles for a Tilemap. When it reads from the file it just takes in the name and some data
	of each tile in the image. See assets/image/tileset/tileset_guide.txt.

	DO NOT CREATE INSTANCES OF TILESETS. New tilesets are create through the Tilemap class
*/

class Tileset{
private:

	std::string file_name;

	std::string name;
	int tile_width;
	int tile_height;

	int size_x;
	int size_y;

	int buffer_x=0;
	int buffer_y=0;

	std::vector<std::string> tileset;

public:
	Tileset(){};
	Tileset(std::string f_p, std::string n_p):file_name(f_p),name(n_p){
		load_from_file();
	}

	void create(std::string f_p, std::string n_p){
		file_name=f_p;
		name=n_p;
		load_from_file();
	}

	std::string get_file_name(){return (file_name+".png");}

	void load_from_file();

	int get_tile_width(){return tile_width;}
	int get_tile_height(){return tile_height;}
	int get_size_x(){return size_x;}
	int get_size_y(){return size_y;}
	int get_buffer_x(){return buffer_x;}
	int get_buffer_y(){return buffer_y;}
	std::string get_name(){return name;}

	int type_s_to_int(std::string);

	std::string at(int i_p){return tileset.at(i_p);}
	int get_set_size(){return tileset.size();}

};

#endif