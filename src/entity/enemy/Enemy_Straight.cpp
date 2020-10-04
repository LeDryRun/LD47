#include "Enemy_Straight.hpp"
#include "../Bullet/Bullet_Manager.hpp"

Enemy_Straight::Enemy_Straight()
{
	animations.push_back(Animation("Straight_Idle"));
	m_stats = EnemyStats(false, 100, 1, 2, 30, 1, 0);
}

Enemy_Straight::Enemy_Straight(Bullet_Manager * bullet_manager, Player * player)
{
	animations.push_back(Animation("Straight_Idle"));
	m_stats = EnemyStats(false, 100, 1, 2, 30, 1, 0);

	m_bullet_manager = bullet_manager;
	m_player = player;

	m_length = 100;
	m_distance_travelled = 0;
	m_dir = 1;

	m_fire_timer = 0;

	m_spawned = false;
	m_spawning = false;

	m_bullet_spawn_points.push_back(Point(0, 0));
}

Enemy_Straight::~Enemy_Straight()
{
}

void Enemy_Straight::update()
{
	if (m_spawned) {
		flight_path();
		if (m_fire_timer >= m_stats.fire_delay_) {
			fire();
			m_fire_timer = 0;
		}

		m_fire_timer++;
	}
	else if (m_spawning) {
		spawn_path();
	}
}

void Enemy_Straight::flight_path()
{
	if (m_distance_travelled >= m_length) {
		m_dir = -m_dir;
		m_distance_travelled = 0;
	}

	set_movement(Point(m_stats.speed_*m_dir,0));
	move();

	sf::Sprite current_animation = animations.at(0).get_current_frame();
	rotate_animations(180 + 180 / M_PI * atan2((m_player->get_center().get_y() - get_center().get_y()), (m_player->get_center().get_x() - get_center().get_x())));

	m_distance_travelled++;
}

void Enemy_Straight::spawn_path()
{
	m_spawning = false;
	m_spawned = true;
	m_stats.radius_ = get_hitbox().get_radius();
}

void Enemy_Straight::fire()
{
	std::vector<Bullet_Blueprint> bullets;
	for (int i = 0; i < m_bullet_spawn_points.size(); i++) {
		float x = m_bullet_spawn_points.at(i).get_x();
		float y = m_bullet_spawn_points.at(i).get_y();

		float rot = getCurrentAnimation().get_current_frame().getRotation();


		sf::Vector2f spawn = getCurrentAnimation().get_current_frame().getTransform().transformPoint(x, y);

		Point dir = Point(-cos(rot*M_PI / 180), -sin(rot*M_PI / 180));
		dir.normalize();

		bullets.push_back(Bullet_Blueprint(BULLET_TYPES::LINEAR, m_stats.damage_, dir, Point(get_center().get_x(), get_center().get_y()), m_stats.bullet_speed_, this));
	}
	m_bullet_manager->add_bullets(bullets);
}

void Enemy_Straight::doSpawn()
{
	m_spawning = true;
}

Animation Enemy_Straight::getCurrentAnimation()
{
	return animations.at(0);
}

EnemyType Enemy_Straight::get_type()
{
	return kEnemyStraight;
}

Enemy_Straight Enemy_Straight::create_copy(Point center, int radius)
{
	create(center, radius);
	return *this;
}

Enemy_Straight Enemy_Straight::create_copy(Spawn_Data data)
{
	create_copy(data.pos, data.radius);
	return *this;
}

