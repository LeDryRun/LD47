#ifndef ENEMY_BOSS_HPP
#define ENEMY_BOSS_HPP

#include "Enemy.hpp"

class Enemy_Boss : public Enemy
{

public:
	Enemy_Boss();
	Enemy_Boss(Bullet_Manager* bullet_manager);
	~Enemy_Boss();
	virtual void update();
	virtual void doSpawn();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void set_origin(Point p_p);

	Animation getCurrentAnimation();
	virtual EnemyType get_type();
	Enemy_Boss create_copy(Point center, int radius);
	Enemy_Boss create_copy(Spawn_Data data);

private:
	int m_length;
	int m_distance_travelled;
	int m_dir;

	virtual void flight_path();
	virtual void spawn_path();
	virtual void fire();
};

#endif //ENEMY_BOSS_HPP