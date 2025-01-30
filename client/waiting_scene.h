#ifndef _WAITING_SCENE_H_
#define _WAITING_SCENE_H_

#include "scene.h"
#include "scene_manager.h"
#include "resources_manager.h"

#include "player.h"
#include "player_hajimi.h"

#include "camera.h"
#include "button.h"
#include "timer.h"

#include <vector>

extern HWND hwnd;
extern httplib::Client* client;
extern Player* player_self;
extern std::vector<Player*> players;
extern const int player_max_num;

class WaitingScene : public Scene
{
public:
	WaitingScene()
	{
		fade_timer.set_wait_time(FADE_TIME);
		fade_timer.set_one_shot(true);
		fade_timer.set_on_timeout([&]()
			{
				SceneManager::instance()->switch_to(SceneManager::SceneType::Game);
			});
	}
	~WaitingScene() = default;

    void on_enter()
    {
		login_to_server(hwnd, ResourcesManager::instance()->find_address());
    }

    void on_render()
    {
		settextcolor(RGB(195, 195, 195));
		if (!Event2::instance()->is_connect)
			outtextxy(15, 675, _T("正在连接中……"));
		else if(!Event2::instance()->is_matched)
			outtextxy(15, 675, _T("比赛即将开始，等待其他玩家进入……"));
		else
		{
			setfillcolor(RGB(color, color, color));
			solidrectangle(0, 0, 1280, 720);
			outtextxy(15, 675, _T("游戏开始……"));
		}
    }

    void on_update(float delta)
    {
		httplib::Result result = client->Post("/player_num");
		if (result && result->status == 200)
		{
			if (std::stoi(result->body) >= 2)
			{
				Event2::instance()->is_matched = true;
			}
		}

		if (Event2::instance()->is_matched)
		{
			fade_timer.on_update(delta);

			fade_progress += FADE_SPEED * delta;
			if (fade_progress >= 1) fade_progress = 1;
			color = lerp(0, 255, fade_progress);
		}
    }

    void on_input(const ExMessage& msg)
    {
			
    }

private:
	Timer fade_timer;
	const float FADE_TIME = 1.0f;
	const float FADE_SPEED = 1.0f;
	float fade_progress = 0;
	float color = 0;

private:
	void login_to_server(HWND hwnd, std::string address)
	{
		client = new httplib::Client(address);
		client->set_keep_alive(true);

		std::thread([&]()
			{
				httplib::Result result = client->Post("/login");
				if (!result || result->status != 200)
				{
					MessageBox(hwnd, _T("无法连接到服务器！"), _T("启动失败"), MB_OK | MB_ICONERROR);
					exit(-1);
				}

				if (std::stoi(result->body) < player_max_num)
				{
					player_self = players[std::stoi(result->body)];
					player_self->set_can_control();
				}
				else
				{
					MessageBox(hwnd, _T("比赛已经开始了"), _T("拒绝加入"), MB_OK | MB_ICONERROR);
					exit(-1);
				}

				Event2::instance()->is_connect = true;

				Sleep(300);
			}).detach();

	}

	float lerp(float start, float end, float t)
	{
		return (1 - t) * start + t * end;
	}
};

#endif