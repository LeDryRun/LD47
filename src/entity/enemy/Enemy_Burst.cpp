#include "Enemy_Burst.hpp"
#include <iostream>

Enemy_Burst::Enemy_Burst()
{
	animations.push_back(Animation("red_circle"));
	m_health = 1;
}

Enemy_Burst::Enemy_Burst(Bullet_Manager * bullet_manager)
{
	animations.push_back(Animation("red_circle"));
	m_bullet_manager = bullet_manager;

	m_length = 100;
	m_distance_travelled = 0;
	m_speed = 1;
	m_dir = 1;
	m_damage = 1;
	m_bullet_speed = 2;

	m_fire_delay = 10;
	m_fire_timer = 0;

	m_health = 100;

	m_spawning = false;
	m_spawned = false;

	m_bullet_spawn_points.push_back(Point(0, 0));
	m_bullet_spawn_points.push_back(Point(32, 0));
	m_bullet_spawn_points.push_back(Point(32, 32));
	m_bullet_spawn_points.push_back(Point(0, 32));

}

Enemy_Burst::~Enemy_Burst()
{
}

void Enemy_Burst::update()
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

void Enemy_Burst::doSpawn()
{
	m_spawning = true;
}

void Enemy_Burst::flight_path()
{
	if (m_distance_travelled >= m_length) {
		m_dir = -m_dir;
		m_distance_travelled = 0;
	}
	
	sf::Sprite current_animation = animations.at(0).get_current_frame();
	rotate_animations( current_animation.getRotation() + 1 );
	std::cout << animations.at(0).get_current_frame().getRotation() << std::endl;

	set_movement(Point(m_speed*m_dir, 0));
	move();

	m_distance_travelled++;
}

void Enemy_Burst::spawn_path()
{
	m_spawning = false;
	m_spawned = true;
}

void Enemy_Burst::fire()
{
	std::vector<Bullet_Blueprint> bullets;
	for (int i = 0; i < m_bullet_spawn_points.size(); i++) {
		float x = m_bullet_spawn_points.at(i).get_x();
		float y = m_bullet_spawn_points.at(i).get_y();

		sf::Vector2f spawn = getCurrentAnimation().get_current_frame().getTransform().transformPoint(x, y);

		Point dir = Point(spawn.x - get_center().get_x(), spawn.y -get_center().get_y());
		dir.normalize();

		bullets.push_back(Bullet_Blueprint(BULLET_TYPES::LINEAR, m_damage, dir, Point(spawn.x, spawn.y), m_bullet_speed));
	}
	m_bullet_manager->add_bullets(bullets);
}

Animation Enemy_Burst::getCurrentAnimation()
{
	return animations.at(0);
}

Enemy_Burst Enemy_Burst::create_copy(Point center, int radius)
{
	create(center, radius);
	return *this;
}

Enemy_Burst Enemy_Burst::create_copy(Spawn_Data data)
{
	create_copy(data.pos, data.radius);
	return *this;
}