#include "UIHandler.hpp"

void UIHandler::load_animations(Imagehandler& image_handler)
{
    // Load Animations
    // Health Sprite
    a_Health[0] = Animation("Health_UI");
    image_handler.load_animation(a_Health[0]);

    a_Health[0].scale(Point(0.75, 0.75));
    a_Health[0].set_position(Point(world->left + (a_Health[0].get_frame_width() / 2) + 5, world->bottom - (a_Health[0].get_frame_height() / 2) - 5));
    a_Health[0].set_looping(false);

    a_Health[1] = Animation("Health_Bar");
    image_handler.load_animation(a_Health[1]);

    a_Health[1].scale(Point(0.75, 0.75));
    a_Health[1].set_position(Point(world->left + (a_Health[1].get_frame_width() / 2) + 5, world->bottom - (a_Health[1].get_frame_height() / 2) - 5));
    a_Health[1].set_looping(false);

    // Line Bar
    a_LineBar[0] = Animation("Linebar_corner");
    a_LineBar[1] = Animation("Linebar_topbot");
    a_LineBar[2] = Animation("Linebar_corner");
    a_LineBar[3] = Animation("Linebar_side");
    a_LineBar[4] = Animation("Linebar_back");
    a_LineBar[5] = Animation("Linebar_side");
    a_LineBar[6] = Animation("Linebar_corner");
    a_LineBar[7] = Animation("Linebar_topbot");
    a_LineBar[8] = Animation("Linebar_corner");
    a_LineBar[9] = Animation("Linebar_bar");

    for (int i = 0; i < 10; i++)
    {
        image_handler.load_animation(a_LineBar[i]);
        a_LineBar[i].set_looping(false);
        a_LineBar[i].scale(Point(1.f, 1.f));
    }

    a_LineBar[8].set_position(Point(world->active_left - (a_LineBar[8].get_frame_width() / 2) - 15, world->active_bottom - (a_LineBar[8].get_frame_height() / 2)));
    a_LineBar[7].set_position(a_LineBar[8].get_position() - Point(a_LineBar[8].get_frame_width() / 2 + a_LineBar[7].get_frame_width() /2, 0.0f));
    a_LineBar[6].set_position(a_LineBar[7].get_position() - Point(a_LineBar[7].get_frame_width() / 2 + a_LineBar[6].get_frame_width() / 2, 0.0f));
    a_LineBar[8].set_rotation(180);
    a_LineBar[6].set_rotation(-90);

    a_LineBar[5].set_position(a_LineBar[8].get_position() - Point(0.0f, a_LineBar[8].get_frame_height() / 2 + a_LineBar[5].get_frame_height() / 2));
    a_LineBar[4].set_position(a_LineBar[5].get_position() - Point(a_LineBar[5].get_frame_width() / 2 + a_LineBar[4].get_frame_width() / 2, 0.0f));
    a_LineBar[3].set_position(a_LineBar[4].get_position() - Point(a_LineBar[4].get_frame_width() / 2 + a_LineBar[3].get_frame_width() / 2, 0.0f));

    a_LineBar[2].set_position(a_LineBar[5].get_position() - Point(0.0f, a_LineBar[5].get_frame_height() / 2 + a_LineBar[2].get_frame_height() / 2));
    a_LineBar[1].set_position(a_LineBar[2].get_position() - Point(a_LineBar[2].get_frame_width() / 2 + a_LineBar[1].get_frame_width() / 2, 0.0f));
    a_LineBar[0].set_position(a_LineBar[1].get_position() - Point(a_LineBar[1].get_frame_width() / 2 + a_LineBar[0].get_frame_width() / 2, 0.0f));
    a_LineBar[2].set_rotation(90);

    a_LineBar[9].set_position(a_LineBar[4].get_position());;
}


void UIHandler::update(float health_ratio, float line_ratio)
{
    f_Line_Ratio = line_ratio;
    f_Health_Ratio = health_ratio;
}

void UIHandler::draw(sf::RenderWindow& window)
{
    // Draw health
    window.draw(a_Health[0].get_current_frame());
    sf::Shader circular;
    if (circular.loadFromFile("../assets/shader/sh_3_4_CircularBar.fsh", sf::Shader::Fragment))
    {
        circular.setUniform("BaseTexture", sf::Shader::CurrentTexture);
        circular.setUniform("uv_topLeft", sf::Vector2f(0.0, 0.5));
        circular.setUniform("uv_botRight", sf::Vector2f(1.0, 1.0));
        circular.setUniform("percentage", f_Health_Ratio);
        window.draw(a_Health[1].get_current_frame(), &circular);
    }

    // Draw Line bar
    for (int i = 0; i < 9; i++)
    { window.draw(a_LineBar[i].get_current_frame()); }
    sf::Shader vertical;
    if (vertical.loadFromFile("../assets/shader/sh_VerticalBar.fsh", sf::Shader::Fragment))
    {
        vertical.setUniform("BaseTexture", sf::Shader::CurrentTexture);
        vertical.setUniform("v_bounds", sf::Vector2f(0.66, 1.0));
        vertical.setUniform("percentage", f_Line_Ratio);
        window.draw(a_LineBar[9].get_current_frame(), &vertical);
    }
}