#ifndef UIHANDLER_HPP
#define UIHANDLER_HPP

#include "../../../image/Imagehandler.hpp"
#include "../../../communal/LDUtil.hpp"

//sf::Shader sh_VerticalBar;

class UIHandler
{
    private:
        World_Data* world;

        Animation a_Health[2];
        Animation a_LineBar[10];
        Animation a_BossBar[10];
        Animation a_PowerUpShelf;
        std::vector<Animation> v_Powerups;

        float f_Health_Ratio = 1.0f;
        float f_Line_Ratio = 1.0f;

    public:
        UIHandler() {};
        UIHandler(World_Data& world_pointer) { world = &world_pointer; };

        void load_animations(Imagehandler& image_handler);
        void update(float health_ratio, float line_ratio);
        void draw(sf::RenderWindow& window);
};

#endif // !UIHANDLER_HPP