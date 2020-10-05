#include "Enemy_Boss.hpp"
#include "../Bullet/Bullet_Manager.hpp"

Enemy_Boss::Enemy_Boss()
{
	animations.push_back(Animation("boss_body"));
	animations.push_back(Animation("boss_west_wing"));
	animations.push_back(Animation("boss_west_gun"));
	animations.push_back(Animation("boss_east_wing"));
	animations.push_back(Animation("boss_east_gun"));
	m_stats = EnemyStats(true, 1000, 10, 5, 10, 0.25f, 0);
}

Enemy_Boss::Enemy_Boss(Bullet_Manager * bullet_manager)
{
	animations.push_back(Animation("boss_body"));
	animations.push_back(Animation("boss_west_wing"));
	animations.push_back(Animation("boss_west_gun"));
	animations.push_back(Animation("boss_east_wing"));
	animations.push_back(Animation("boss_east_gun"));
	m_stats = EnemyStats(true, 1000, 10, 5, 10, 0.25f, 0);

	m_bullet_manager = bullet_manager;

	m_length = 100;
	m_distance_travelled = 0;
	m_dir = 1;

	m_fire_timer = 0;

	m_spawning = false;
	m_spawned = false;
}

Enemy_Boss::~Enemy_Boss()
{
}

void Enemy_Boss::update()
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

void Enemy_Boss::doSpawn()
{
	m_spawning = true;
}

void Enemy_Boss::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	for (int i = 0; i < animations.size(); i++)
		target.draw(animations.at(i).get_current_frame(), states);
}

void Enemy_Boss::set_origin(Point p_p)
{
	/*animations.at(0).get_current_frame().setOrigin(p_p.get_x(), p_p.get_y());
	animations.at(1).get_current_frame().setOrigin(p_p.get_x() - animations.at(1).get_frame_width() - animations.at(0).get_frame_width() / 2, p_p.get_y());
	animations.at(2).get_current_frame().setOrigin(p_p.get_x() - animations.at(1).get_frame_width() - animations.at(0).get_frame_width() / 2, p_p.get_y() - 152/2);
	animations.at(3).get_current_frame().setOrigin(p_p.get_x() + animations.at(1).get_frame_width() + animations.at(0).get_frame_width() / 2, p_p.get_y());
	animations.at(4).get_current_frame().setOrigin(p_p.get_x() + animations.at(1).get_frame_width() + animations.at(0).get_frame_width() / 2, p_p.get_y() - 183/2);

	for (int i = 0; i < animations.size(); i++) {
		animations.at(i).get_current_frame().setPosition(0, 0);
	}*/
}

Animation Enemy_Boss::getCurrentAnimation()
{
	return animations.at(current_animation_int);
}

EnemyType Enemy_Boss::get_type()
{
	return kEnemyBoss;
}

Enemy_Boss Enemy_Boss::create_copy(Point center, int radius)
{
	m_spawn_point = center;
	create(Point(center.get_x(), -2 * radius), radius);

	m_stats.radius_ = radius;
	return *this;
}

Enemy_Boss Enemy_Boss::create_copy(Spawn_Data data)
{
	create_copy(data.pos, data.radius);
	return *this;
}

void Enemy_Boss::flight_path()
{
	if (m_distance_travelled >= m_length) {
		m_dir = -m_dir;
		m_distance_travelled = 0;
	}

	sf::Sprite current_animation = getCurrentAnimation().get_current_frame();

	set_movement(Point(m_stats.speed_*m_dir, 0));
	move();

	m_distance_travelled++;
}

void Enemy_Boss::spawn_path()
{
	float posy = get_center().get_y();
	float targety = m_spawn_point.get_y();

	sf::Sprite body = animations.at(0).get_current_frame();

	set_origin(Point(body.getLocalBounds().width/2, body.getLocalBounds().height/2));

	if (targety - posy != 0) {
		Point dir(0, targety - posy);
		dir.normalize();

		set_movement(Point(0, m_stats.speed_*dir.get_y()));
		move();
	}
	else {
		m_spawning = false;
		m_spawned = true;
	}
}

void Enemy_Boss::fire()
{
	std::vector<Bullet_Blueprint> bullets;
	for (int i = 0; i < m_bullet_spawn_points.size(); i++) {
		float x = m_bullet_spawn_points.at(i).get_x();
		float y = m_bullet_spawn_points.at(i).get_y();

		float rot = getCurrentAnimation().get_current_frame().getRotation() - 30 - i * 120;

		sf::Vector2f spawn = getCurrentAnimation().get_current_frame().getTransform().transformPoint(x, y);

		Point dir = Point(-cos(rot*M_PI / 180), -sin(rot*M_PI / 180));
		dir.normalize();

		bullets.push_back(Bullet_Blueprint(BULLET_TYPES::LINEAR, m_stats.damage_, dir, Point(spawn.x, spawn.y), m_stats.bullet_speed_, this));
	}
	m_bullet_manager->add_bullets(bullets);
}
