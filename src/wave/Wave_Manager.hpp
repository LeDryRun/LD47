#ifndef WAVE_MANAGER_HPP
#define WAVE_MANAGER_HPP

#include "Wave.hpp"
#include "../entity/enemy/Enemy.hpp"
#include "../entity/enemy/Enemy_Straight.hpp"
#include "../entity/enemy/Enemy_Burst.hpp"
#include "../entity/enemy/Enemy_Sine.hpp"
#include "../entity/enemy/Enemy_V.hpp"
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
	int get_current_wave();
	float get_wave_difficulty();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	std::vector<Enemy*> m_enemies;
	std::vector<Wave> m_wave_buffer;
	Enemy_Straight m_enemy_straight;
	Enemy_Burst m_enemy_burst;
	Enemy_Sine m_enemy_sine;
	Enemy_V m_enemy_v;
	Bullet_Manager* m_bullet_manager;
	Player* m_player;
	World_Data* m_world_data;
	std::vector<Tick_Timer> m_spawn_timers;
	int m_wave_number;
	float m_wave_difficulty;
	std::vector<Wave> m_wave_templates;

};

#endif //WAVE_MANAGER_HPP