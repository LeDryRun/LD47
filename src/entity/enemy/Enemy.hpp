#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <vector>

#include "../Circular_Entity.hpp"
#include "../Bullet/Bullet_Manager.hpp"

class Enemy : public Circular_Entity
{

public:
	Enemy(Bullet_Manager* bullet_manager);
	Enemy();
	~Enemy();
	virtual void update() = 0;
	virtual void flight_path() = 0;
	virtual void fire() = 0;

protected:
	bool m_boss;
	float m_health;
	int m_damage;
	float m_bullet_speed;
	int m_fire_delay;
	int m_fire_timer;
	float m_speed;
	std::vector<Bullet*> m_bullets;
	Bullet_Manager* m_bullet_manager;
	std::vector<Point> m_bullet_spawn_points;


};

#endif //ENEMY_HPP