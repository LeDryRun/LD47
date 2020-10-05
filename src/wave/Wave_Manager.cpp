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
	initial_wave_time=3000;
	next_wave=Tick_Timer(initial_wave_time);
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

	Enemy_Type_Pool type_pool={{kEnemyStraight,kEnemyBurst,kEnemySine,kEnemyV}};
	std::vector<Spawn_Data> spawn_data={
		Spawn_Data(0,false,false,Point(0.5f,0.1f),30),
		Spawn_Data(0,false,false,Point(0.2f,0.1f),60),
		Spawn_Data(0,false,false,Point(0.7f,0.1f),1)
	};
	int wave_difficulty=1;

	wave_templates.push_back(Wave(type_pool,false,spawn_data,wave_difficulty));


	type_pool={{kEnemyStraight,kEnemyBurst,kEnemySine,kEnemyV},{kEnemyStraight,kEnemyBurst,kEnemySine,kEnemyV},{kEnemyStraight,kEnemyBurst,kEnemySine,kEnemyV}};
	spawn_data={
		Spawn_Data(0,false,false,Point(0.5f,0.1f),30),
		Spawn_Data(1,false,false,Point(0.2f,0.1f),60),
		Spawn_Data(2,false,false,Point(0.7f,0.1f),1)
	};
	wave_difficulty=1;

	wave_templates.push_back(Wave(type_pool,false,spawn_data,wave_difficulty));

	type_pool={{kEnemyStraight}};
	spawn_data={
		Spawn_Data(0,false,false,Point(0.1f,0.1f),0),
		Spawn_Data(0,false,false,Point(0.3f,.1f),40),
		Spawn_Data(0,false,false,Point(0.5f,0.1f),80),

	};
	wave_difficulty=2;

	wave_templates.push_back(Wave(type_pool,false,spawn_data,wave_difficulty));

	type_pool={{kEnemySine}};
	spawn_data={
		Spawn_Data(0,false,true,Point(0.1f,0.1f),0),
		Spawn_Data(0,false,true,Point(0.3f,.1f),40),
		Spawn_Data(0,false,true,Point(0.5f,0.1f),80),

	};
	wave_difficulty=2;

	wave_templates.push_back(Wave(type_pool,false,spawn_data,wave_difficulty));


	type_pool={{kEnemyBurst}};
	spawn_data={
		Spawn_Data(0,false,false,Point(0.1f,0.1f),0),
		Spawn_Data(0,false,false,Point(0.5f,0.2f),20),
		Spawn_Data(0,false,false,Point(0.2f,0.35f),40),
		Spawn_Data(0,false,false,Point(0.3f,0.15f),60),
		Spawn_Data(0,false,false,Point(0.7f,0.25f),80),
		Spawn_Data(0,false,false,Point(0.9f,0.25f),100),
		Spawn_Data(0,false,false,Point(0.8f,0.3f),120),

	};
	wave_difficulty=5;

	wave_templates.push_back(Wave(type_pool,false,spawn_data,wave_difficulty));
}



Wave_Manager::~Wave_Manager()
{
	for (int i = 0; i < enemies.size(); i++) {
		delete enemies.at(i);
	}
}


void Wave_Manager::add_enemy(Spawn_Data spawn_data){
	switch(static_cast<EnemyType>(spawn_data.enemy_type)){
		case kEnemyStraight:enemies.push_back(new Enemy_Straight(enemy_straight.create_copy(spawn_data)));enemies.back()->doSpawn();break;
		case kEnemyBurst:enemies.push_back(new Enemy_Burst(enemy_burst.create_copy(spawn_data)));enemies.back()->doSpawn();break;
		case kEnemySine:enemies.push_back(new Enemy_Sine(enemy_sine.create_copy(spawn_data)));enemies.back()->doSpawn();break;
		case kEnemyV:enemies.push_back(new Enemy_V(enemy_v.create_copy(spawn_data)));enemies.back()->doSpawn();break;
		default:break;
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
			add_enemy(current_waves.at(i).enemies_to_spawn.at(j));
		}
		current_waves.at(i).enemies_to_spawn.clear();
		if(current_waves.at(i).spawn_data.size()==0){
			current_waves.erase(current_waves.begin()+i);
		}
	}

	// for current enemies update

	for(int i=0;i<(int)enemies.size();i++){
		if(enemies.at(i)->is_alive()){
			enemies.at(i)->update();
		}else{
			enemies.erase(enemies.begin()+i);
			i--;
		}
	}

	if(enemies.size()==0){
		generate_waves();
		next_wave.restart();
	}
	if(next_wave.do_timer_loop()){
		generate_waves();
	}


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
		spawn_data.at(i).pos=Point(opos.get_x()*world_data->active_width+world_data->active_left,opos.get_y()*world_data->active_height+world_data->active_top)
			+Point(random(-20,20),random(-20,20));
	}

	current_waves.push_back(Wave(wave_pool,boss,spawn_data,difficulty));

	next_wave.set_max(initial_wave_time+waves_defeated*20);
}

