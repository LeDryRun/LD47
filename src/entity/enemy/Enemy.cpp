#include "Enemy.hpp"
#include "../Bullet/Bullet_Manager.hpp"

Enemy::Enemy(Bullet_Manager* bullet_manager)
	: m_bullet_manager(bullet_manager)
{
}

Enemy::Enemy()
{
}

Enemy::~Enemy()
{
}

bool Enemy::is_alive()
{
	return m_health>0;
}

void Enemy::take_damage(float damage)
{
	m_health -= damage;
}

float Enemy::get_health()
{
	return m_health;
}
