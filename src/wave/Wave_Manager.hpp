#ifndef WAVE_MANAGER_HPP
#define WAVE_MANAGER_HPP

#include "Wave.hpp"
#include "../entity/enemy/Enemy.hpp"
#include "../entity/enemy/Enemy_Straight.hpp"
#include "../entity/enemy/Enemy_Burst.hpp"
#include "../entity/enemy/Enemy_Sine.hpp"
#include "../entity/enemy/Enemy_V.hpp"
#include "../entity/enemy/Enemy_Boss.hpp"
#include "../communal/Tick_Timer.hpp"

#include <deque>

class Wave_Manager : public sf::Drawable
{
public:
	Wave_Manager(Bullet_Manager* bullet_manager, Player* player, World_Data* world_data);
	Wave_Manager();
	~Wave_Manager();

	void add_wave(const Wave& wave);
	void update();
	void generate_waves();
	void load_animations(Imagehandler& imagehandler);
	void load_templates();

	void add_enemy(Spawn_Data);

	void create();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	std::vector<Enemy*> enemies;
	std::vector<Wave> current_waves;

	Enemy_Straight enemy_straight;
	Enemy_Burst enemy_burst;
	Enemy_Sine enemy_sine;
	Enemy_V enemy_v;
	Enemy_Boss enemy_boss;

	Bullet_Manager* bullet_manager;
	Player* player;
	World_Data* world_data;

	int waves_defeated=0;
	float current_difficulty=0;
	float desired_difficulty=0;
	std::vector<Wave> wave_templates;

	Tick_Timer next_wave;
	int initial_wave_time;

};

#endif //WAVE_MANAGER_HPP