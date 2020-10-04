#ifndef WAVE_HPP
#define WAVE_HPP

#include <vector>
#include <deque>

#include "../entity/Point.hpp"


struct Spawn_Data {

	Spawn_Data(int enemy_type, int radius, Point pos, float spawn_delay)
		: enemy_type(enemy_type), radius(radius), pos(pos), spawn_delay(spawn_delay)
	{
	}

	int enemy_type;
	int radius;
	Point pos;
	float spawn_delay;
};

enum EnemyType {
	kEnemyStraight,
	kEnemyBurst,
	kEnemySine,
	kEnemyV,
	kEnemyHoming
};

struct Wave {

	Wave(std::vector<EnemyType> enemies, bool boss, std::deque<Spawn_Data> spawn_data)
		: enemies(enemies), boss(boss), spawn_data(spawn_data)
	{
	}
	Wave() {}
	std::vector<EnemyType> enemies;
	bool boss;
	std::deque<Spawn_Data> spawn_data;

};



#endif //WAVE_HPP