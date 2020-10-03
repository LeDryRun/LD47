#include "Enemy_Straight.hpp"

Enemy_Straight::Enemy_Straight()
{
	animations.push_back(Animation("green_circle"));
}

Enemy_Straight::Enemy_Straight(Bullet_Manager * bullet_manager, Player * player)
{
	animations.push_back(Animation("green_circle"));

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

	m_bullet_spawn_points.push_back(Point(0, 0));
	m_bullet_spawn_points.push_back(Point(32, 0));
	m_bullet_spawn_points.push_back(Point(32, 32));
	m_bullet_spawn_points.push_back(Point(0, 32));
}

Enemy_Straight::~Enemy_Straight()
{
}

void Enemy_Straight::update()
{
	flight_path();
	if (m_fire_timer >= m_fire_delay) {
		fire();
		m_fire_timer = 0;
	}

	m_fire_timer++;
}

void Enemy_Straight::flight_path()
{
	if (m_distance_travelled >= m_length) {
		m_dir = -m_dir;
		m_distance_travelled = 0;
	}

	set_movement(Point(m_speed*m_dir,0));
	move();

	m_distance_travelled++;
}

void Enemy_Straight::fire()
{
	std::vector<Bullet_Blueprint> bullets;
	for (int i = 0; i < m_bullet_spawn_points.size(); i++) {
		float x = m_bullet_spawn_points.at(i).get_x();
		float y = m_bullet_spawn_points.at(i).get_y();

		sf::Vector2f spawn = getCurrentAnimation().get_current_frame().getTransform().transformPoint(x, y);
		
		Point dir = Point(m_player->get_center().get_x() - spawn.x, m_player->get_center().get_y() - spawn.y);

		bullets.push_back(Bullet_Blueprint(BULLET_TYPES::LINEAR, m_damage, dir, Point(spawn.x, spawn.y), m_bullet_speed));
	}
	m_bullet_manager->add_bullets(bullets);
}

Animation Enemy_Straight::getCurrentAnimation()
{
	return animations.at(0);
}
