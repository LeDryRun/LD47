#ifndef ENEMY_BURST_HPP
#define ENEMY_BURST_HPP

#include "Enemy.hpp"

class Enemy_Burst : public Enemy
{
public:
	Enemy_Burst();
	Enemy_Burst(Bullet_Manager* bullet_manager);
	~Enemy_Burst();
	virtual void update();
	virtual void flight_path();
	virtual void fire();
	Animation getCurrentAnimation();

private:
	int m_length;
	int m_distance_travelled;
	int m_dir;
};

#endif //ENEMY_STRAIGHT_HPP