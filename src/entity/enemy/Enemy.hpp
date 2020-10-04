#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <vector>

#include "../Circular_Entity.hpp"

class Bullet_Manager;
class Bullet;

class Enemy : public Circular_Entity
{

public:
	Enemy(Bullet_Manager* bullet_manager);
	Enemy();
	~Enemy();
	virtual void update() = 0;
	virtual void doSpawn() = 0;

	bool is_alive();
	void take_damage(float damage);
	float get_health();

protected:
	bool m_boss;
	float m_health;
	int m_damage;
	float m_bullet_speed;
	int m_fire_delay;
	int m_fire_timer;
	float m_speed;
	bool m_spawned;
	bool m_spawning;
	std::vector<Bullet*> m_bullets;
	Bullet_Manager* m_bullet_manager;
	std::vector<Point> m_bullet_spawn_points;

	virtual void flight_path() = 0;
	virtual void spawn_path() = 0;
	virtual void fire() = 0;


};

#endif //ENEMY_HPP