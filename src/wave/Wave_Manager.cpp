#include "Wave_Manager.hpp"

Wave_Manager::Wave_Manager(Bullet_Manager* bullet_manager, Player* player)
	: m_bullet_manager(bullet_manager), m_player(player)
{
	m_enemy_straight = Enemy_Straight(m_bullet_manager, m_player);
	m_enemy_burst = Enemy_Burst(m_bullet_manager);
	m_enemy_sine = Enemy_Sine(m_bullet_manager, m_player);
	m_enemy_v = Enemy_V(m_bullet_manager);
}

Wave_Manager::Wave_Manager()
{
}

void Wave_Manager::load_animations(Imagehandler & imagehandler)
{
	m_enemy_straight.load_animations(imagehandler);
	m_enemy_burst.load_animations(imagehandler);
	m_enemy_sine.load_animations(imagehandler);
	m_enemy_v.load_animations(imagehandler);
	m_enemy_straight.scale_animations(Point(32.0f / 360.0f, 32.0f / 360.0f));
	m_enemy_burst.scale_animations(Point(32.0f / 360.0f, 32.0f / 360.0f));
	m_enemy_sine.scale_animations(Point(32.0f / 360.0f, 32.0f / 360.0f));
	m_enemy_v.scale_animations(Point(32.0f / 360.0f, 32.0f / 360.0f));

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
}

void Wave_Manager::update()
{
	for (int i = 0; i < m_wave_buffer.size(); i++) {
		if (m_wave_buffer.at(i).spawn_data.size() > 0) {
			if(&m_spawn_timers.at(i) == NULL)
				m_spawn_timers.at(i) = Tick_Timer(m_wave_buffer.at(i).spawn_data.front().spawn_delay);
			if (m_spawn_timers.at(i).do_timer_loop()) {
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

}

