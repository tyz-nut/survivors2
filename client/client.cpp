#include "../thirdparty/httplib.h"


#include "scene_manager.h"
#include "event2.h"
#include "game_scene.h"
#include "menu_scene.h"
#include "waiting_scene.h"

#include <chrono>
#include <string>
#include <vector>
#include <thread>
#include <codecvt>
#include <fstream>
#include <sstream>

HWND hwnd;
httplib::Client* client = nullptr;		//http�ͻ��˶���
Scene* menu_scene = nullptr;
Scene* game_scene = nullptr;
Scene* waiting_scene = nullptr;
Player* player_self = nullptr;
std::vector<Player*> players;
std::vector<Enemy*> enemys;
const int player_max_num = 2;
const int window_width = 1280;
const int window_height = 720;

int main(int argc, char** argv)
{
	//�������ݳ�ʼ��
	using namespace std::chrono;

	//��Ļ��ʼ��
	hwnd = initgraph(window_width, window_height, EW_SHOWCONSOLE);
	SetWindowText(hwnd, _T("�Ҵ��ߣ�"));
	settextstyle(28, 0, _T("IPix"));
	setbkmode(TRANSPARENT);

	try
	{
		ResourcesManager::instance()->load(hwnd);
	}
	catch (const LPCTSTR id)
	{
		TCHAR err_msg[512];
		_stprintf_s(err_msg, _T("�޷����أ�%s"), id);
		MessageBox(hwnd, err_msg, _T("��Դ����ʧ��"), MB_OK | MB_ICONERROR);
		return -1;
	}

	menu_scene = new MenuScene();
	game_scene = new GameScene();
	waiting_scene = new WaitingScene();
	MapManager::instance()->map_init();
	SceneManager::instance()->scene_init();
	PlayerManager::instance()->player_init();
	EnemyManager::instance()->enemy_init();
	ExMessage msg;

	//��Ϸʱ���ʼ��
	const nanoseconds frame_duration(1000000000 / 144);
	steady_clock::time_point last_tick = steady_clock::now();

	BeginBatchDraw();

	while (!Event2::instance()->is_quit)
	{
		//�����������
		while (peekmessage(&msg))
		{
			SceneManager::instance()->on_input(msg);

			switch (msg.message)
			{
			case WM_KEYUP:
				//Q
				if (msg.vkcode == 0x51)
					Event2::instance()->is_debug = !Event2::instance()->is_debug;
				break;
			default:
				break;
			}
		}

		//������Ϸ����
		steady_clock::time_point frame_start = steady_clock::now();
		duration<float> delta = duration<float>(frame_start - last_tick);

		SceneManager::instance()->on_update(delta.count());

		//���������
		setbkcolor(RGB(0, 0, 0));
		cleardevice();

		SceneManager::instance()->on_render();
		if (Event2::instance()->is_debug)
		{
			settextcolor(RGB(255, 0, 0));
			outtextxy(15, 15, _T("�ѿ�������ģʽ������Q���ر�"));
		}

		FlushBatchDraw();

		last_tick = frame_start;
		nanoseconds sleep_duration = frame_duration - (steady_clock::now() - frame_start);
		if (sleep_duration > nanoseconds(0))
			std::this_thread::sleep_for(sleep_duration);
	}

	return 0;
}