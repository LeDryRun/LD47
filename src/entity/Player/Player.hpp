#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "../Circular_Entity.hpp"
#include "../../communal/LDUtil.hpp"
#include "../Bullet/Bullet_Manager.hpp"

#include <iostream>

class Player : public Circular_Entity
{
    private:
        Bullet_Manager* p_BulletMan;
		sf::Texture t_Ring;
		sf::Sprite s_Ring;

        float f_PlayerSpd = 10.f;

        std::vector<Point> v_Line;
        float f_LineLimit = 5.0f;
        float f_LineLeft = f_LineLimit;
        bool b_isLooping = false;

    public:
        Player(){ 
			animations.push_back(Animation("Player_Core_Idle"));
			if (!t_Ring.loadFromFile("../assets/image/animations/Player_Bod.png", sf::IntRect(0, 0, 310, 310))) {
				std::cout << "Failed to load Ring Texture!\n";
			}
            t_Ring.setSmooth(true);
			s_Ring.setTexture(t_Ring);
			s_Ring.setOrigin(t_Ring.getSize().x / 2, t_Ring.getSize().y / 2);
		}
        Player(Bullet_Manager* b_man)
        {
            animations.push_back(Animation("Player_Core_Idle"));
            p_BulletMan = b_man;
			if (!t_Ring.loadFromFile("../assets/image/animations/Player_Bod.png", sf::IntRect(0, 0, 310, 310))) {
				std::cout << "Failed to load Ring Texture!\n";
			}
            t_Ring.setSmooth(true);
			s_Ring.setTexture(t_Ring);
			s_Ring.setOrigin(t_Ring.getSize().x / 2, t_Ring.getSize().y / 2);
        }

        float get_PlayerSpd() { return f_PlayerSpd; };
        void set_PlayerSpd(int i) { f_PlayerSpd = i; };
        std::vector<Point> get_Line() { return v_Line; };
        float get_LineLimit() { return f_LineLimit; };
        void set_LineLimit(float f) { f_LineLimit = f; };
        float get_LineLeft() { return f_LineLeft; };
        void set_LineLeft(float f) { f_LineLeft = f; };
        bool get_isLooping() { return b_isLooping; };
        void set_isLooping(bool b) { b_isLooping = b; };

        void update(World_Data world, Point move, bool shifted);
        void draw(World_Data world, sf::RenderWindow& window);
		virtual void scale_animations(Point);
        void start_loop();
        void validate_loop();
};

#endif