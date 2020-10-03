#ifndef Tilemap_Entity_HPP
#define Tilemap_Entity_HPP

#include "Entity.hpp"

/*
	An entity designed to be used with a tilemap. needs a copy of whatever tilemap you're using it for upon creation simply for setting tile sizes and the like,
	therefore switching it to a different tilemap with equivalent sizes shouldn't be an issue. To switch an instance to a new tilemap with different sizes
	or to be thorough simply re-call the create() method 

*/

class Tilemap;

class Tilemap_Entity: public Entity{
protected:
	Point current_tile=Point(0,0);

	std::vector<Point> tiles_colliding;

	Point hitbox_size_in_tiles=Point(0,0);
	Point tile_size=Point(0,0);

public:
	Tilemap_Entity(){};

	void create(Point p_p, Tilemap);//point is initial grid location. by default if an animation has been added creates a hitbox with frame dimensions.
	//(fixed the bug where if there was no animation yet it would crash)
	void create_hitbox(Point size_p, Point offset_p) override;//offsets are working a little strangely atm and I haven't been able to track it down,
	//so pass (0,0) or use with caution 

	Point get_current_tile(){return current_tile;}


	virtual void update(Tilemap&);
	virtual void tilemap_collide_physics(Tilemap&);//this will change the movement member in order to constrict the hitbox not to collide with "solid" tiles in the tilemap 
	virtual bool check_tilemap_collision(Tilemap& tilemap);// returns true if the current movement would cause the hitbox to collide with solid tiles, but makes no actual changes
};

#endif