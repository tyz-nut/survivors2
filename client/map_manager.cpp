#include "map_manager.h"

MapManager* MapManager::manager = nullptr;

MapManager* MapManager::instance()
{
	if (!manager)
	{
		manager = new MapManager();
	}

	return manager;
}

const Map& MapManager::find_map(std::string str) const
{
	for (auto itor : maps)
	{
		if (itor->name.compare(str) == 0)
		{
			return *itor;
		}
	}
	return error;
}

const Map& MapManager::find_map(int id) const
{
	for (auto itor : maps)
	{
		if (itor->id == id)
		{
			return *itor;
		}
	}
	return error;
}