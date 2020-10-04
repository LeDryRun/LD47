#include "Enemy_V.hpp"
#include "../Bullet/Bullet_Manager.hpp"

Enemy_V::Enemy_V()
{
	animations.push_back(Animation("Fish_Idle"));
	m_health = 1;
}

Enemy_V::Enemy_V(Bullet_Manager * bullet_manager)
{
	animations.push_back(Animation("Fish_Idle"));

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
	m_spawned = false;
	m_spawning = false;
	
	m_bullet_spawn_points.push_back(Point(16,16));
	m_bullet_spawn_points.push_back(Point(16,16));
}

Enemy_V::~Enemy_V()
{
}

void Enemy_V::update()
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

void Enemy_V::flight_path()
{
	if (m_distance_travelled >= m_length) {
		m_dir = -m_dir;
		m_distance_travelled = 0;
	}

	set_movement(Point(0, m_speed*m_dir));
	move();

	m_distance_travelled++;
}

void Enemy_V::spawn_path()
{
	m_spawning = false;
	m_spawned = true;
}

void Enemy_V::fire()
{
	std::vector<Bullet_Blueprint> bullets;
	for (int i = 0; i < m_bullet_spawn_points.size(); i++) {
		float x = m_bullet_spawn_points.at(i).get_x();
		float y = m_bullet_spawn_points.at(i).get_y();

		sf::Vector2f spawn = getCurrentAnimation().get_current_frame().getTransform().transformPoint(x, y);
		sf::Vector2f corner = getCurrentAnimation().get_current_frame().getTransform().transformPoint(i==0?0:32, 32);

		Point dir = Point(corner.x - spawn.x, corner.y - spawn.y);
		dir.normalize();

		bullets.push_back(Bullet_Blueprint(BULLET_TYPES::LINEAR, m_damage, dir, Point(spawn.x, spawn.y), m_bullet_speed,this));
	}
	m_bullet_manager->add_bullets(bullets);
}

void Enemy_V::doSpawn()
{
	m_spawning = true;
}

Animation Enemy_V::getCurrentAnimation()
{
	return animations.at(0);
}

Enemy_V Enemy_V::create_copy(Point center, int radius)
{
	create(center, radius);
	return *this;
}

Enemy_V Enemy_V::create_copy(Spawn_Data data)
{
	create_copy(data.pos, data.radius);
	return *this;
}


