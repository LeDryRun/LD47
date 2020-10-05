#ifndef ENEMY_BOSS_HPP
#define ENEMY_BOSS_HPP

#include "Enemy.hpp"
#include "Enemy_Straight.hpp"
#include "../../communal/Tick_Timer.hpp"

class Enemy_Boss : public Enemy
{

public:
	Enemy_Boss();
	Enemy_Boss(Bullet_Manager* bullet_manager, Player* player, World_Data* world_data);
	~Enemy_Boss();
	virtual void update();
	virtual void doSpawn();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual std::vector<Spawn_Data> get_babies();

	void set_origin(Point p_p);

	Animation getCurrentAnimation();
	virtual EnemyType get_type();
	Enemy_Boss create_copy(Point center, int radius);
	Enemy_Boss create_copy(Spawn_Data data);

private:
	int m_length;
	int m_distance_travelled;
	int m_dir;
	bool m_open;
	bool m_transitioning;
	Tick_Timer m_cycle_timer;
	float rot_offset;
	Enemy_Straight m_enemy_straight;
	World_Data* m_world_data;
	Player* m_player;
	std::vector<Spawn_Data> m_babies;

	virtual void flight_path();
	virtual void spawn_path();
	virtual void fire();
	void update_arms();
};

#endif //ENEMY_BOSS_HPP