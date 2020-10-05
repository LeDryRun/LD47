#include "Wave_Manager.hpp"
#include "../communal/Communal.hpp"


Wave_Manager::Wave_Manager(Bullet_Manager* bullet_manager, Player* player, World_Data* world_data)
	: bullet_manager(bullet_manager), player(player), world_data(world_data)
{
	enemy_straight = Enemy_Straight(bullet_manager, player);
	enemy_burst = Enemy_Burst(bullet_manager);
	enemy_sine = Enemy_Sine(bullet_manager, player);
	enemy_v = Enemy_V(bullet_manager);
	enemies= std::vector<Enemy*>();
	load_templates();

}

Wave_Manager::Wave_Manager()
{	
}

void Wave_Manager::create(){
	//next_wave=Tick_Timer(100);
	generate_waves();
	//enemies.push_back(new Enemy_V(enemy_v.create_copy(Spawn_Data(0,false,Point(400,30),0))));
	//enemies.at(0)->doSpawn();

}

void Wave_Manager::load_animations(Imagehandler & imagehandler)
{
	enemy_straight.load_animations(imagehandler);
	enemy_burst.load_animations(imagehandler);
	enemy_sine.load_animations(imagehandler);
	enemy_v.load_animations(imagehandler);
	enemy_straight.scale_animations(Point(32.0f / 360.0f, 32.0f / 360.0f));
	enemy_burst.scale_animations(Point(48.0f / 360.0f, 48.0f / 360.0f));
	enemy_sine.scale_animations(Point(32.0f / 360.0f, 32.0f / 360.0f));
	enemy_v.scale_animations(Point(32.0f / 343.0f, 32.0f / 323.0f));
}

void Wave_Manager::load_templates(){

	Enemy_Type_Pool type_pool={{kEnemyStraight,kEnemyBurst,kEnemySine,kEnemyV},{kEnemyStraight,kEnemyBurst,kEnemySine,kEnemyV}};
	std::vector<Spawn_Data> spawn_data={
		Spawn_Data(0,false,Point(0.5f,0.05f),30),
		Spawn_Data(1,false,Point(0.2f,0.05f),1)
	};
	int wave_difficulty=5;

	wave_templates.push_back(Wave(type_pool,false,spawn_data,wave_difficulty));


	type_pool={{kEnemyStraight}};
	spawn_data={
		Spawn_Data(0,false,Point(0.1f,0.05f),0),
		Spawn_Data(0,false,Point(0.3f,.05f),40),
		Spawn_Data(0,false,Point(0.5f,0.05f),80),

	};
	wave_difficulty=5;

	wave_templates.push_back(Wave(type_pool,false,spawn_data,wave_difficulty));


	type_pool={{kEnemyBurst}};
	spawn_data={
		Spawn_Data(0,false,Point(0.1f,0.1f),0),
		Spawn_Data(0,false,Point(0.5f,0.2f),20),
		Spawn_Data(0,false,Point(0.2f,0.35f),40),
		Spawn_Data(0,false,Point(0.3f,0.15f),60),
		Spawn_Data(0,false,Point(0.7f,0.25f),80),
		Spawn_Data(0,false,Point(0.6f,0.05f),100),
		Spawn_Data(0,false,Point(0.8f,0.3f),120),

	};
	wave_difficulty=5;

	wave_templates.push_back(Wave(type_pool,false,spawn_data,wave_difficulty));


	/*Point center = Point(m_world_data->width / 2, m_world_data->height / 2);

	std::vector<EnemyType> enemies;
	enemies.push_back(EnemyType::kEnemyStraight);
	enemies.push_back(EnemyType::kEnemyBurst);
	enemies.push_back(EnemyType::kEnemySine);
	enemies.push_back(EnemyType::kEnemyV);

	std::deque<Spawn_Data> spawn_data;

	//single enemy
	spawn_data.push_back(Spawn_Data(0, 16, Point(500, 100), 100));

	m_wave_templates.push_back(Wave(enemies,false,spawn_data));*/
}



Wave_Manager::~Wave_Manager()
{
	for (int i = 0; i < enemies.size(); i++) {
		delete enemies.at(i);
	}
}


void Wave_Manager::update()
{

	//determine current desired difficulty level based on time spent in game/number of waves defeated


	//determine current actual difficulty level	based on current spawning waves and persistent enemies


	// if neccessary push back new wave based on difference between desired and actual using templates

	// for current waves spawn enemies if neccessary

	for(int i=0;i<(int)current_waves.size();i++){
		current_waves.at(i).update();
		for(int j=0;j<(int)current_waves.at(i).enemies_to_spawn.size();j++){
			Spawn_Data spawn_data=current_waves.at(i).enemies_to_spawn.at(j);
			switch(static_cast<EnemyType>(spawn_data.enemy_type)){
				case kEnemyStraight:enemies.push_back(new Enemy_Straight(enemy_straight.create_copy(spawn_data)));enemies.back()->doSpawn();break;
				case kEnemyBurst:enemies.push_back(new Enemy_Burst(enemy_burst.create_copy(spawn_data)));enemies.back()->doSpawn();break;
				case kEnemySine:enemies.push_back(new Enemy_Sine(enemy_sine.create_copy(spawn_data)));enemies.back()->doSpawn();break;
				case kEnemyV:enemies.push_back(new Enemy_V(enemy_v.create_copy(spawn_data)));enemies.back()->doSpawn();break;
				default:break;
			}
		}
		current_waves.at(i).enemies_to_spawn.clear();
		if(current_waves.at(i).spawn_data.size()==0){
			current_waves.erase(current_waves.begin()+i);
		}
	}

	// for current enemies update

	for(int i=0;i<(int)enemies.size();i++){
		enemies.at(i)->update();
	}





	/*
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
	}*/

}

void Wave_Manager::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	for (int i = 0; i < enemies.size(); i++) {
		target.draw(*enemies.at(i));
	}
}

void Wave_Manager::generate_waves()
{

	Point center = Point(world_data->width / 2, world_data->height / 2);
	Point opos;


	//AI LOGIC
	int r= random(0,wave_templates.size()-1);

	Wave blueprint= wave_templates.at(r);

	Enemy_Type_Pool wave_pool={};
	std::vector<Spawn_Data> spawn_data=blueprint.spawn_data;
	bool boss=blueprint.boss;
	int difficulty=0;

	std::vector<EnemyType> types_chosen={};
	for(int i=0;i<(int)blueprint.enemy_type_pool.size();i++){
		int pool_size=blueprint.enemy_type_pool.at(i).size()-1;

		//AI LOGIC
		r= random(0,pool_size);

		types_chosen.push_back(blueprint.enemy_type_pool.at(i).at(r));
	}

	for(int i=0;i<(int)spawn_data.size();i++){
		spawn_data.at(i).enemy_type=(int)types_chosen.at(spawn_data.at(i).enemy_type);
		opos=spawn_data.at(i).pos;
		spawn_data.at(i).pos=Point(opos.get_x()*world_data->active_width+world_data->active_left,opos.get_y()*world_data->active_height+world_data->active_top);
	}

	current_waves.push_back(Wave(wave_pool,boss,spawn_data,difficulty));
}

