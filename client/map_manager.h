#ifndef _MAP_MANAGER_
#define _MAP_MANAGER_

#include "vector2.h"
#include <string>
#include <vector>
#include <graphics.h>

struct Map
{
	int id = 0;
	std::string name = "";
	Vector2 area = Vector2(0, 0);
	Vector2 player_position = Vector2(0, 0);
	float enemy_pig_spawnl_interva = 0;
	int enemy_pig_max_num = 0;
};

class MapManager
{
public:
	static MapManager* instance();

	const Map& find_map(std::string str) const
	{
		for (auto itor : maps)
		{
			if (itor->name.compare(str) == 0)
			{
				return *itor;
			}
		}
	}

	const Map& find_map(int id) const
	{
		for (auto itor : maps)
		{
			if (itor->id == id)
			{
				return *itor;
			}
		}
	}

private:
	static MapManager* manager;
	Map map_default;
	std::vector<Map*> maps;

private:
	MapManager()
	{
		map_default = { 0, "default", Vector2(2560, 1440), Vector2(1280, 720), 1, 20 };
		maps.push_back(&map_default);
	}
	~MapManager() = default;
};

MapManager* MapManager::manager = nullptr;

MapManager* MapManager::instance()
{
	if (!manager)
	{
		manager = new MapManager();
	}

	return manager;
}

#endif // !_MAP_MANAGER_
