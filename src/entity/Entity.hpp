#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "Hitbox.hpp"
#include "Point.hpp"
#include "../image/Animation.hpp"
#include "SFML/Graphics.hpp"
#include <vector>

class Imagehandler;

/*
	Entity holds collision and image data. add_animation shoudl be called in the constructor of your entity derived class. the string passed into add_animation needs to
	EXACTLY equal the name of some animation that has already been loaded by the Imagehandler, otherwise you'll just see a rotating error symbol 
	in the constructor of your state class you should call load_animations AFTER all desired animations have been added. animations added after load_animations will have no texture
	applied to them, and will simply be blank.

	By default the create() method will generate a hitbox the same size as the first animation added, to specify hitbox size use create_hitbox() AFTER create()
	(the bug that caused the program to crash if there was no first animation has been resolved, but you should still specify adding animations before creating an instance)

	Inhereits sf::Drawable, to render call window.draw(this) in your gamestate's render function. you must explicitly call animate() somewhere each tick or the frames wont update
*/


class Entity:public sf::Drawable{

protected:
	Hitbox hitbox;
	Point hitbox_offset=Point(0,0);
	std::vector<Animation> animations;
	int current_animation_int=0;// window.draw(this) will draw the current frame of the animation at this index in the animations vector

	Point position=Point(0,0);//top left

	Point movement=Point(0,0);//change in position to be applied when you call move()

	Hitbox projected_hitbox;//used internally to check for collisions

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

public:
	Entity(){};

	virtual void create(Point p_p);//point in world space
	virtual void create_hitbox(Point size_p, Point offset_p);

	Animation& ref_animation(int i_p){return animations.at(i_p);}//editing animations directly is HIGHLY discouraged!
	void set_current_animation(int i_p){current_animation_int=i_p;}//use this to switch which animation will be displayed when you cann window.draw(this)
	virtual void animate();//needs to be called every tick to advance the animation to the next frame when appropriate 

	void add_animation(std::string name_p){animations.push_back(Animation(name_p));}//DO THIS IN THE CONSTRUCTOR

	Hitbox get_hitbox(){return hitbox;}
	Hitbox& ref_hitbox(){return hitbox;}

	Point get_movement(){return movement;}
	Point& ref_movement(){return movement;}
	void set_movement(Point p_p){movement=p_p;}

	void set_position(Point p_p);
	Point get_position(){return position;}
	Point get_center(){return position+Point(hitbox.get_width()/2,hitbox.get_height()/2);}


	virtual void move();//Doesn't check for collisions unless you tell it to!
	virtual void load_animations(Imagehandler&);

};


#endif