#include "../thirdparty/httplib.h"
#include <mutex>
#include <string>
#include <iostream>
#include <fstream>

#include "player_server.h"

std::mutex g_mutex;			//全局互斥锁
int player_num = 0;
const int player_max_num = 2;
PlayerServer* player_1 = new PlayerServer();
PlayerServer* player_2 = new PlayerServer();
std::vector<PlayerServer*> players = { player_1, player_2 };


void split_string(const std::string& s, std::vector<std::string>& v, const char c)
{
	std::string::size_type pos1, pos2;
	pos2 = s.find(c);
	pos1 = 0;
	while (std::string::npos != pos2)
	{
		v.push_back(s.substr(pos1, pos2 - pos1));

		pos1 = pos2 + 1;
		pos2 = s.find(c, pos1);
	}
}


int main(int argc, char** argv)
{
	httplib::Server server;
	std::cout << "服务器已搭建";


	server.Post("/login", [&](const httplib::Request& req, httplib::Response& res)
		{
			std::lock_guard<std::mutex> lock(g_mutex);

			if (player_num > player_max_num)
				player_num = player_max_num;
			players[player_num]->set_id(player_num);

			std::string str = std::to_string(player_num);
			res.set_content(str, "text/plain");
			player_num += 1;
		});

	server.Post("/player_num", [&](const httplib::Request& req, httplib::Response& res)
		{
			std::lock_guard<std::mutex> lock(g_mutex);

			std::string str = std::to_string(player_num);
			res.set_content(str, "text/plain");
		});

	server.Post("/update_player", [&](const httplib::Request& req, httplib::Response& res)
		{
			std::lock_guard<std::mutex> lock(g_mutex);

			std::string str = req.body;
			
			std::vector<std::string> information;
			split_string(str, information, ';');
			int id = std::stoi(information[0]);
			players[id]->set_position(Vector2::stoV(information[1]));
			players[id]->set_velocity(Vector2::stoV(information[2]));

			std::cout << "id == 0 " + players[0]->get_position().Vtos() + ";" + players[0]->get_velocity().Vtos() << " / ";
			std::cout << "id == 1 " + players[1]->get_position().Vtos() + ";" + players[1]->get_velocity().Vtos() << std::endl;

			str = "";
			for (size_t i = 0; i < players.size(); i++)
			{
				str += players[i]->get_position().Vtos() + ";" + players[i]->get_velocity().Vtos() + ";/";
			}
			res.set_content(str, "text/plain");
		});

	server.listen("0.0.0.0", 25565);

	return 0;
}