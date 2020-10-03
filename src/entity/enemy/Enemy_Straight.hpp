#ifndef ENEMY_STRAIGHT_HPP
#define ENEMY_STRAIGHT_HPP

#include "Enemy.hpp"

class Enemy_Straight : public Enemy
{
public:
	Enemy_Straight();
	Enemy_Straight(Bullet_Manager* bullet_manager, Player* player);
	~Enemy_Straight();
	virtual void update();
	virtual void flight_path();
	virtual void fire();
	Animation getCurrentAnimation();

private:
	int m_length;
	int m_distance_travelled;
	int m_dir;
	Player* m_player;
};

#endif //ENEMY_STRAIGHT_HPP