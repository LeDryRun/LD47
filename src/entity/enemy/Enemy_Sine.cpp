#include "Enemy_Sine.hpp"
#include "../../communal/LDUtil.hpp"
#include "../Bullet/Bullet_Manager.hpp"
#include <math.h>

Enemy_Sine::Enemy_Sine()
{
	animations.push_back(Animation("Sine_Idle"));
	m_health = 1;
}

Enemy_Sine::Enemy_Sine(Bullet_Manager * bullet_manager, Player * player)
{
	animations.push_back(Animation("Sine_Idle"));

	m_bullet_manager = bullet_manager;
	m_player = player;

	m_length = 100;
	m_distance_travelled = 0;
	m_speed = 1;
	m_dir = 1;
	m_damage = 1;
	m_bullet_speed = 2;

	m_fire_delay = 10;
	m_fire_timer = 0;

	m_health = 100;
	m_spawned = false;
	m_spawning = false;

	m_bullet_spawn_points.push_back(Point(16,16));
}

Enemy_Sine::~Enemy_Sine()
{
}

void Enemy_Sine::update()
{
	if (m_spawned) {
		flight_path();
		if (m_fire_timer >= m_fire_delay) {
			fire();
			m_fire_timer = 0;
		}

		m_fire_timer++;
	}
	else if (m_spawning) {
		spawn_path();
	}
}

void Enemy_Sine::flight_path()
{
	if (m_distance_travelled >= m_length) {
		m_dir = -m_dir;
		m_distance_travelled = 0;
	}

	set_movement(Point(m_speed*m_dir, 0));
	move();
	sf::Sprite current_animation = animations.at(0).get_current_frame();
	rotate_animations(180+180/M_PI*atan2((m_player->get_center().get_y()-get_center().get_y()),(m_player->get_center().get_x() - get_center().get_x())));

	m_distance_travelled++;
}

void Enemy_Sine::spawn_path()
{
	m_spawning = false;
	m_spawned = true;
}

void Enemy_Sine::fire()
{
	std::vector<Bullet_Blueprint> bullets;
	for (int i = 0; i < m_bullet_spawn_points.size(); i++) {
		float x = m_bullet_spawn_points.at(i).get_x();
		float y = m_bullet_spawn_points.at(i).get_y();

		float rot = getCurrentAnimation().get_current_frame().getRotation();


		sf::Vector2f spawn = getCurrentAnimation().get_current_frame().getTransform().transformPoint(x, y);
		
		Point dir = Point(-cos(rot*M_PI/180), -sin(rot*M_PI/180));
		dir.normalize();

		bullets.push_back(Bullet_Blueprint(BULLET_TYPES::SINE, m_damage, dir, Point(get_center().get_x(), get_center().get_y()), m_bullet_speed, this));
	}
	m_bullet_manager->add_bullets(bullets);
}

void Enemy_Sine::doSpawn()
{
	m_spawning = true;
}

Animation Enemy_Sine::getCurrentAnimation()
{
	return animations.at(0);
}

Enemy_Sine Enemy_Sine::create_copy(Point center, int radius)
{
	create(center, radius);
	return *this;
}

Enemy_Sine Enemy_Sine::create_copy(Spawn_Data data)
{
	create_copy(data.pos, data.radius);
	return *this;
}

