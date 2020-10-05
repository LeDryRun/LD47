#include "Wave_Manager.hpp"
#include "../communal/Communal.hpp"

#include <unordered_map>
#include <functional>
#include <set>

Wave_Manager::Wave_Manager(Bullet_Manager* bullet_manager, Player* player, World_Data* world_data)
	: m_bullet_manager(bullet_manager), m_player(player), m_world_data(world_data)
{
	m_enemy_straight = Enemy_Straight(m_bullet_manager, m_player);
	m_enemy_burst = Enemy_Burst(m_bullet_manager);
	m_enemy_sine = Enemy_Sine(m_bullet_manager, m_player);
	m_enemy_v = Enemy_V(m_bullet_manager);
	m_enemy_boss = Enemy_Boss(m_bullet_manager, player, world_data);

	m_wave_number = 0;
	m_wave_difficulty = 0;
}

Wave_Manager::Wave_Manager()
{	m_wave_number = 0;
	m_wave_difficulty = 0;
}

void Wave_Manager::load_animations(Imagehandler & imagehandler)
{
	m_enemy_straight.load_animations(imagehandler);
	m_enemy_burst.load_animations(imagehandler);
	m_enemy_sine.load_animations(imagehandler);
	m_enemy_v.load_animations(imagehandler);
	m_enemy_boss.load_animations(imagehandler);

	m_enemy_straight.scale_animations(Point(32.0f / 360.0f, 32.0f / 360.0f));
	m_enemy_burst.scale_animations(Point(48.0f / 360.0f, 48.0f / 360.0f));
	m_enemy_sine.scale_animations(Point(32.0f / 360.0f, 32.0f / 360.0f));
	m_enemy_v.scale_animations(Point(32.0f / 343.0f, 32.0f / 323.0f));
	m_enemy_boss.scale_animations(Point(64.0f / 308.0f, 64.0f / 308.0f));

}

void Wave_Manager::load_templates()
{
	Point center = Point(m_world_data->width / 2, m_world_data->height / 2);

	std::vector<EnemyType> enemies;
	enemies.push_back(EnemyType::kEnemyStraight);
	enemies.push_back(EnemyType::kEnemyBurst);
	enemies.push_back(EnemyType::kEnemySine);
	enemies.push_back(EnemyType::kEnemyV);

	std::deque<Spawn_Data> spawn_data;

	//single enemy
	spawn_data.push_back(Spawn_Data(0, 16, Point(500, 100), 100));

	m_wave_templates.push_back(Wave(enemies,false,spawn_data));
}

int Wave_Manager::get_current_wave()
{
	return m_wave_number;
}

float Wave_Manager::get_wave_difficulty()
{
	return m_wave_difficulty;
}

Wave_Manager::~Wave_Manager()
{
	for (int i = 0; i < m_enemies.size(); i++) {
		delete m_enemies.at(i);
	}
}

void Wave_Manager::add_wave(const Wave & wave)
{
	m_wave_buffer.push_back(wave);
	m_spawn_timers.push_back(NULL);
	m_wave_number++;
}

void Wave_Manager::update()
{
	for (int i = 0; i < m_wave_buffer.size(); i++) {
		if (m_wave_buffer.at(i).spawn_data.size() > 0) {
			if(&m_spawn_timers.at(i) == NULL)
				m_spawn_timers.at(i) = Tick_Timer(m_wave_buffer.at(i).spawn_data.front().spawn_delay);
			if (m_spawn_timers.at(i).do_timer_loop()) {
				if (m_wave_buffer.at(i).enemies.size() <= m_wave_buffer.at(i).spawn_data.front().enemy_type)
					m_wave_buffer.at(i).spawn_data.front().enemy_type = m_wave_buffer.at(i).enemies.size() - 1;
				switch (m_wave_buffer.at(i).enemies.at(m_wave_buffer.at(i).spawn_data.front().enemy_type)) {
				case kEnemyStraight:
					m_enemies.push_back(new Enemy_Straight(m_enemy_straight.create_copy(m_wave_buffer.at(i).spawn_data.front())));
					m_enemies.back()->doSpawn();
					m_wave_buffer.at(i).spawn_data.pop_front();
					break;
				case kEnemyBurst:
					m_enemies.push_back(new Enemy_Burst(m_enemy_burst.create_copy(m_wave_buffer.at(i).spawn_data.front())));
					m_enemies.back()->doSpawn();
					m_wave_buffer.at(i).spawn_data.pop_front();
					break;
				case kEnemySine:
					m_enemies.push_back(new Enemy_Sine(m_enemy_sine.create_copy(m_wave_buffer.at(i).spawn_data.front())));
					m_enemies.back()->doSpawn();
					m_wave_buffer.at(i).spawn_data.pop_front();
					break;
				case kEnemyV:
					m_enemies.push_back(new Enemy_V(m_enemy_v.create_copy(m_wave_buffer.at(i).spawn_data.front())));
					m_enemies.back()->doSpawn();
					m_wave_buffer.at(i).spawn_data.pop_front();
					break;
				case kEnemyBoss:
					m_enemies.push_back(new Enemy_Boss(m_enemy_boss.create_copy(m_wave_buffer.at(i).spawn_data.front())));
					m_enemies.back()->doSpawn();
					m_wave_buffer.at(i).spawn_data.pop_front();
					break;
				}
			}
		}
	}

	std::vector<Wave> temp_wave;
	std::vector<Tick_Timer> temp_timers;

	for (int i = 0; i < m_wave_buffer.size(); i++)
	{
		if (m_wave_buffer.at(i).spawn_data.size() > 0) {
			temp_wave.push_back(m_wave_buffer.at(i));
			temp_timers.push_back(m_spawn_timers.at(i));
		}
	}
	
	m_wave_buffer = temp_wave;
	m_spawn_timers = temp_timers;

	std::vector<Enemy*> enemy_buffer;

	for (int i = 0; i < m_enemies.size(); i++) {
		if (m_enemies.at(i)->is_alive()) {
			enemy_buffer.push_back(m_enemies.at(i));
		}
		else {
			delete m_enemies.at(i);
		}
	}

	m_enemies = enemy_buffer;

	for (int i = 0; i < m_enemies.size(); i++) {
		m_enemies.at(i)->update();
	}
}

void Wave_Manager::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	for (int i = 0; i < m_enemies.size(); i++) {
		target.draw(*m_enemies.at(i));
	}
}

void Wave_Manager::generate_waves()
{
	m_wave_difficulty = 10 * m_wave_number + 12;

	std::unordered_map< EnemyType, float> difficulty_map;
	
	difficulty_map.emplace(kEnemyStraight, m_enemy_straight.get_stats().get_difficulty_score());
	difficulty_map.emplace(kEnemyBurst, m_enemy_burst.get_stats().get_difficulty_score());
	difficulty_map.emplace(kEnemySine, m_enemy_sine.get_stats().get_difficulty_score());
	difficulty_map.emplace(kEnemyV, m_enemy_v.get_stats().get_difficulty_score());

	typedef std::function<bool(std::pair<EnemyType, float>, std::pair<EnemyType, float>)> Comparator;
	Comparator compFunctor =
		[](std::pair<EnemyType, float> elem1, std::pair<EnemyType, float> elem2)
	{
		return elem1.second > elem2.second;
	};
	std::set<std::pair<EnemyType, float>, Comparator> difficulty_set(
		difficulty_map.begin(), difficulty_map.end(), compFunctor);
	
	std::vector<Enemy*> difficulty_order;

	for (std::pair<EnemyType, float> element : difficulty_set) {
		switch (element.first) {
		case kEnemyStraight:
			difficulty_order.push_back(&m_enemy_straight);
			break;
		case kEnemyBurst:
			difficulty_order.push_back(&m_enemy_burst);
			break;
		case kEnemySine:
			difficulty_order.push_back(&m_enemy_sine);
			break;
		case kEnemyV:
			difficulty_order.push_back(&m_enemy_v);
			break;
		}
	}

	std::unordered_map< EnemyType, int > enemy_count;

	enemy_count.emplace(kEnemyStraight, 0);
	enemy_count.emplace(kEnemyBurst, 0);
	enemy_count.emplace(kEnemySine, 0);
	enemy_count.emplace(kEnemyV, 0);

	float difficulty_total = 0;

	while (difficulty_total < m_wave_difficulty) {
		float added_difficulty = 0;
		for (int i = 0; i < difficulty_order.size(); i++) {
			if (difficulty_total + difficulty_order.at(i)->get_stats().get_difficulty_score() < m_wave_difficulty) {
				EnemyType type = difficulty_order.at(i)->get_type();
				enemy_count.at(type) = enemy_count.at(type) + 1;
				added_difficulty = difficulty_map.at(type);
				break;
			}
		}
		difficulty_total += added_difficulty;
		if (added_difficulty == 0)
			break;
	}

	std::vector<EnemyType> enemies;
	enemies.push_back(EnemyType::kEnemyStraight);
	enemies.push_back(EnemyType::kEnemyBurst);
	enemies.push_back(EnemyType::kEnemySine);
	enemies.push_back(EnemyType::kEnemyV);

	std::deque<Spawn_Data> spawn_data;

	int x_min = (int)m_world_data->active_left + 100;
	int x_max = (int)m_world_data->active_right - 100;

	int y_max = (int)m_world_data->active_bottom - 400;
	int y_min = (int)m_world_data->active_top;


	for (std::pair<EnemyType, int> element : enemy_count) {
		for (int i = 0; i < element.second; i++){
			spawn_data.push_back(Spawn_Data(element.first, 16, Point(random(x_min, x_max), random(y_min, y_max)), 100));
		}
	}

	Wave wave = Wave(enemies, false, spawn_data);

	add_wave(wave);
	
}

