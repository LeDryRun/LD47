#ifndef TILEMAP_HPP
#define TILEMAP_HPP

#include <vector>
#include <string>
#include "SFML/Graphics.hpp"
#include "Tile.hpp"
#include "Tileset.hpp"
#include <string>
#include <iostream>

/*
The purpose of the Tilemap class is to provide a fast and easy visualization of a grid based game world based on a set of rectangular images.
It statically holds a list of possible tilesets to use, which define a relationship between a set of tile names and thier associated location in a png file.
A new Tileset can be added to this list to be used from anywhere in the proram p by simply calling the add_tileset() function and passing in the file location
(without the file extention!) and a name for the program to use for that tileset. As the class holds it's tilesets statically it is never neccesary to add any
 specific tileset more than once, thus for the time being the add_tileset() calls are located in the Imagehandler class constructor, so as to only be added once.

The Tilemap class is designed to read it's map data from a text file with a ".map" extension, see src/assets/maps/map_guide.txt

When the map is being loaded a VertexArray is loaded with pixel data corresponding to the image of each tile in the map. rotation occurs at 90* angles to maintain grid structure

Tiles are meant to hold primarily visual and collision data. For complex tile behaviour is reccomended to create a separate corresponding entity elsewhere 

Because Tilemaps use a vertexArray they can be sf::Drawable, which means you call window.draw(map) in the render function of your gamestate to display them to the screen

Tilemaps are transformable, but beware! you must use Tilemap.set_posiiton() NOT Transformable.setPosition() otherwise the grid coordinate to world coordinate 
and collision data will be incorrrect!
*/
class Tilemap: public sf::Drawable, public sf::Transformable{
private:
	//static list of all available tilesets
	static std::vector<Tileset> tilesets;

	//specific tileset to use in this instance, determined by the map data
	Tileset tileset;

	//list of tiles with some basic info and optional collision data (collision with tiles only occurs with Tilemap_Entities, and only when the tilesare within range)
	std::vector<Tile> map;

	//instance of texture to be used by the tileset. this is deprecated, but I didn't have time to finalize doing it the way I wanted so were stuck with this
	sf::Texture tile_texture;
	//the vertex array to be printed to the screen
	sf::VertexArray vertex_array;
	//index of the tileset to be used in this instance. I believe this is also deprecated, but don't mess with it rn
	int tileset_num;

	int length_x=-1;
	int length_y=-1;

	//top left position of the map itself in world space
	Point position;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

public:

	Tilemap(){}
	Tilemap(std::string f_p){load_from_file(f_p);}

	void load_from_file(std::string);

	Tile get_tile(int x_p,int y_p){return map.at(x_p+ y_p*length_x);}
	Tile& ref_tile(int x_p,int y_p){return map.at(x_p+ y_p*length_x);}//making direct changes to tiles is discouraged! use set_tile_type

	Tile get_tile(Point p_p){return map.at(p_p.get_x()+ p_p.get_y()*length_x);}
	Tile& ref_tile(Point p_p){return map.at(p_p.get_x()+ p_p.get_y()*length_x);}//making direct changes to tiles is discouraged! use set_tile_type

	int get_length_x(){return length_x;}
	void set_length_x(int i_p){length_x=i_p;}
	
	int get_length_y(){return length_y;}
	void set_length_y(int i_p){length_y=i_p;}

	Point get_position(){return position;}
	void set_position(Point p_p){
		position=p_p;
		setPosition(position.get_x(),position.get_y());
		for(int i=0;i<length_x;i++){
			for(int j=0;j<length_y;j++){
				ref_tile(i,j).ref_hitbox().set_position(position.get_x()+tileset.get_tile_width()*i,position.get_y()+tileset.get_tile_height()*j);
			}
		}
	}

	Tileset get_tileset(){return tileset;}

	//very useful for getting world posisiton of anything on the map
	Point tile_coord_to_position(int x_p, int y_p){
		return Point(x_p*tileset.get_tile_width() +position.get_x(), y_p*tileset.get_tile_height()+position.get_y());
	}
	Point tile_coord_to_position(Point p_p){
		return Point(p_p.get_x()*tileset.get_tile_width() +position.get_x(), p_p.get_y()*tileset.get_tile_height()+position.get_y());
	}

	//very useful for finding the grid coordinate of anyting given world position
	Point position_to_tile_coord(Point p_p){
		if(p_p.get_x()<position.get_x() || p_p.get_x()>position.get_x()+length_x*tileset.get_tile_width() 
			||p_p.get_y()<position.get_y() || p_p.get_y()>position.get_y()+length_y*tileset.get_tile_height()){
			return Point(-1,-1);
		}else{
			return Point((p_p.get_x()-position.get_x())/tileset.get_tile_width(),(p_p.get_y()-position.get_y())/tileset.get_tile_height());
		}
	}

	void set_tile_type(int,int,int);//really meant for internal use. don't use this unless you read it through and understand what it does
	void set_tile_type(Point,std::string);// USE THIS ONE. simply give a grid coordinae and the name of the new tile_type
	void load_tile(int,int,std::string);//really meant for internal use. don't use this unless you read it through and understand what it does
	void set_tile_rotation(int,int,int);//x and y grid positions, rotation number: 0=0* 1=90* 2=180*,3=270* any thing past 3 just gets modulus


	static void add_tileset(std::string,std::string);


	std::vector<Point> find_path(Point start, Point end);//simple A* pathfinding, uses the tiles' solid member. parameters are in grid coordinates

};

#endif