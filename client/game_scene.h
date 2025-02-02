#ifndef _GAME_SCENE_H_
#define _GAME_SCENE_H_

#include <codecvt>

#include "scene.h"
#include "timer.h"
#include "countdown.h"
#include "resources_manager.h"
#include "player_manager.h"
#include "enemy_manager.h"

extern httplib::Client* client;
extern Player* player_self;
extern std::vector<Player*> players;
extern std::vector<Enemy*> enemys;
extern const int player_max_num;
extern const int window_width;
extern const int window_height;

class GameScene : public Scene
{
public:
    enum class GameStage
    {
        Ready,		//准备起跑倒计时
        Racing, 	//比赛中
        over,       //结束
    };
public:
    GameScene() = default;
    ~GameScene() = default;

    void on_enter()
    {
        map = MapManager::instance()->find_map("default");
        PlayerManager::instance()->player_on_game(map);
        EnemyManager::instance()->enemy_on_game(map);
        
        player_self_position = PlayerManager::instance()->get_self_position();
        player_self_velocity = PlayerManager::instance()->get_self_velocity();
        img_background = ResourcesManager::instance()->find_image(map.name);

        std::thread([&]()
		{
			while (!Event2::instance()->is_game_over)
			{
				using namespace std::chrono;

				std::string route = "/update_player";

                std::string body = player_information(player_self->get_id(), player_self_position, player_self_velocity);

				httplib::Result result = client->Post(route, body, "text/plain");
				if (result && result->status == 200)
				{
                    std::vector<std::string> information;
                    std::vector<Vector2> position;
                    std::vector<Vector2> velocity;
                    split_string(result->body, information, '/');
                    for (size_t i = 0; i < players.size(); i++)
                    {
                        if(player_self->get_id() == i)
                            continue;
                        std::vector<std::string> info;
                        split_string(information[i], info, ';');
                        players[i]->set_position(Vector2::stoV(info[0]));
                        players[i]->set_velocity(Vector2::stoV(info[1]));
                    }
                    EnemyManager::instance()->set_random_num(std::stoi(information[players.size()]));
                    /*std::cout << "id == 0 " + players[0]->get_position().Vtos() + ";" + players[0]->get_velocity().Vtos() << " / ";
                    std::cout << "id == 1 " + players[1]->get_position().Vtos() + ";" + players[1]->get_velocity().Vtos() << std::endl;*/
				}
				std::this_thread::sleep_for(nanoseconds(1000000000 / 60));
			}
		}).detach();

        countdown = new Countdown();

        camera_ui.set_size({ 1280,720 });
        camera_scene.set_size({ 1280,720 });


        
        
// 
// 
//        is_slide_out_started = false;
//
//        pos_img_winner_bar.x = -img_winner_bar.getwidth();
//        pos_img_winner_bar.y = (getheight() - img_winner_bar.getheight()) / 2;
//        pos_x_img_winner_bar_dst = (getwidth() - img_winner_bar.getwidth()) / 2;
//
//        pos_img_winner_text.x = pos_img_winner_bar.x;
//        pos_img_winner_text.y = (getheight() - img_1P_winner.getheight()) / 2;
//        pos_x_img_winner_text_dst = (getwidth() - img_1P_winner.getwidth()) / 2;
//
//        timer_winner_slide_in.restart();
//        timer_winner_slide_in.set_wait_time(2500);
//        timer_winner_slide_in.set_one_shot(true);
//        timer_winner_slide_in.set_callback([&]()
//            {
//                is_slide_out_started = true;
//            });
//
//        timer_winner_slide_out.restart();
//        timer_winner_slide_out.set_wait_time(1000);
//        timer_winner_slide_out.set_one_shot(true);
//        timer_winner_slide_out.set_callback([&]()
//            {
//                scene_manager.switch_to(SceneManager::SceneType::Menu);
//            });
//
//        status_bar_1P.set_avatar(img_player_1_avatar);
//        status_bar_2P.set_avatar(img_player_2_avatar);
//
//        status_bar_1P.set_position(235, 625);
//        status_bar_2P.set_position(675, 625);
//
    }

    void on_update(float delta)
    {
        PlayerManager::instance()->on_update(delta);

        player_self_position = PlayerManager::instance()->get_self_position();
        player_self_velocity = PlayerManager::instance()->get_self_velocity();


        if (stage == GameStage::Ready)
        {
            countdown->on_update(delta);

            if (Event2::instance()->is_ready)
            {
                play_audio(_T("bgm"), true);
                stage = GameStage::Racing;
            }
        }

        if (stage == GameStage::Racing)
        {
            for (Enemy* enemy : enemys)
            {
                int target = enemy->get_random_num() % players.size();
                enemy->set_target_position(players[target]->get_position());
            }
            EnemyManager::instance()->on_update(delta);
            std::cout << enemys[0]->get_position().Vtos() << std::endl;
            /*if ((id_player == 1 && progress_1 >= num_total_char)
                || (id_player == 2 && progress_2 >= num_total_char))
            {
                stop_audio(_T("bgm"));
                play_audio((id_player == 1) ? _T("1p_win") : _T("2p_win"));
                MessageBox(hwnd, _T("赢麻麻！"), _T("游戏结束"), MB_OK | MB_ICONINFORMATION);
                exit(0);
            }
            else if ((id_player == 1 && progress_2 >= num_total_char)
                || (id_player == 2 && progress_1 >= num_total_char))
            {
                stop_audio(_T("bgm"));
                MessageBox(hwnd, _T("输光光！"), _T("游戏结束"), MB_OK | MB_ICONINFORMATION);
                exit(0);
            }*/

        }

        camera_scene.look_at(player_self_position);

//        bullet_list.erase(std::remove_if(bullet_list.begin(), bullet_list.end(),
//            [](const Bullet* bullet)
//            {
//                bool deletable = bullet->check_can_remove();
//                if (deletable)
//                    delete bullet;
//                return deletable;
//            }),
//            bullet_list.end());
//
//        for (Bullet* bullet : bullet_list)
//            bullet->on_update(delta);
//
//        const Vector2& position_player_1 = player_1->get_position();
//        const Vector2& position_player_2 = player_2->get_position();
//        if (position_player_1.y >= getheight())
//            player_1->set_hp(0);
//        if (position_player_2.y >= getheight())
//            player_2->set_hp(0);
//        if (player_1->get_hp() <= 0 || player_2->get_hp() <= 0)
//        {
//            if (!is_game_over)
//            {
//                mciSendString(_T("stop bgm_game"), NULL, 0, NULL);
//                mciSendString(_T("play ui_win from 0"), NULL, 0, NULL);
//            }
//
//            is_game_over = true;
//        }
//
//        status_bar_1P.set_hp(player_1->get_hp());
//        status_bar_1P.set_mp(player_1->get_mp());
//        status_bar_2P.set_hp(player_2->get_hp());
//        status_bar_2P.set_mp(player_2->get_mp());
//
//        if (is_game_over)
//        {
//            pos_img_winner_bar.x += (int)(speed_winner_bar * delta);
//            pos_img_winner_text.x += (int)(speed_winner_text * delta);
//
//            if (!is_slide_out_started)
//            {
//                timer_winner_slide_in.on_update(delta);
//                if (pos_img_winner_bar.x > pos_x_img_winner_bar_dst)
//                    pos_img_winner_bar.x = pos_x_img_winner_bar_dst;
//                if (pos_img_winner_text.x > pos_x_img_winner_text_dst)
//                    pos_img_winner_text.x = pos_x_img_winner_text_dst;
//            }
//            else
//                timer_winner_slide_out.on_update(delta);
//        }
    }
//
    void on_render()
    {
        draw_background();

        EnemyManager::instance()->on_render(camera_scene);
        PlayerManager::instance()->on_render(camera_scene);

        if (stage == GameStage::Ready)
        {
            countdown->on_render(camera_ui);
        }

        if (stage == GameStage::Racing && Event2::instance()->is_debug)
        {
            static std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> convert;
            settextcolor(RGB(255, 0, 0));
            std::string str = "玩家位置：" + player_self_position.Vtos();
            std::wstring wstr = convert.from_bytes(str);
            outtextxy(15, 25, wstr.c_str());
            str = "玩家速度：" + player_self_velocity.Vtos();
            wstr = convert.from_bytes(str);
            outtextxy(15, 35, wstr.c_str());
            str = "野猪数量：" + std::to_string(EnemyManager::instance()->get_enemy_pig_num());
            wstr = convert.from_bytes(str);
            outtextxy(15, 45, wstr.c_str());
        }

//
//        for (const Bullet* bullet : bullet_list)
//            bullet->on_draw(camera);
//
//        if (is_game_over)
//        {
//            putimage_alpha(pos_img_winner_bar.x, pos_img_winner_bar.y, &img_winner_bar);
//            putimage_alpha(pos_img_winner_text.x, pos_img_winner_text.y,
//                player_1->get_hp() > 0 ? &img_1P_winner : &img_2P_winner);
//        }
//        else
//        {
//            status_bar_1P.on_draw();
//            status_bar_2P.on_draw();
//        }
//
//
//
//        {
//            
//
//
//            //绘制界面
//            if (stage == Stage::Racing)
//            {
//                static const Rect rect_textbox =
//                {
//                    0,
//                    720 - img_ui_textbox.getheight(),
//                    img_ui_textbox.getwidth(),
//                    img_ui_textbox.getheight()
//                };
//                static std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> convert;
//                std::wstring wstr_line = convert.from_bytes(str_line_list[idx_line]);
//                std::wstring wstr_completed = convert.from_bytes(str_line_list[idx_line].substr(0, idx_char));
//                putimage_ex(camera_ui, &img_ui_textbox, &rect_textbox);
//                settextcolor(RGB(125, 125, 125));
//                outtextxy(185 + 2, rect_textbox.y + 65 + 2, wstr_line.c_str());
//                settextcolor(RGB(25, 25, 25));
//                outtextxy(185, rect_textbox.y + 65, wstr_line.c_str());
//                settextcolor(RGB(0, 149, 217));
//                outtextxy(185, rect_textbox.y + 65, wstr_completed.c_str());
//            }
//        }
    }

    void on_input(const ExMessage& msg)
    {
        if(stage == GameStage::Racing)
            PlayerManager::instance()->on_input(msg);
    }
//
//    void on_exit()
//    {
//        delete player_1;
//        player_1 = nullptr;
//        delete player_2;
//        player_2 = nullptr;
//
//        is_debug = false;
//
//        bullet_list.clear();
//        main_camera.reset();
//    }
//
//
private:
	Vector2 player_self_position;
    Vector2 player_self_velocity;
	std::vector<Vector2> players_position;
    Map map;
    IMAGE* img_background;
    GameStage stage = GameStage::Ready;

    Countdown* countdown;

    Camera camera_ui;
    Camera camera_scene;


//    StatusBar status_bar_1P;
//    StatusBar status_bar_2P;
//
//
//    POINT pos_img_winner_bar = { 0 };
//    POINT pos_img_winner_text = { 0 };
//    int speed_winner_bar = 8;
//    int speed_winner_text = 5;
//    int pos_x_img_winner_bar_dst = 0;
//    int pos_x_img_winner_text_dst = 0;
//    Timer timer_winner_slide_in;
//    Timer timer_winner_slide_out;
//    bool is_slide_out_started = false;

private:
    void draw_background()
    {
        //绘制背景
        static const Rect rect_bg =
        {
            0, 0,
            (int)map.area.x, (int)map.area.y
        };
        putimage_ex(camera_scene, img_background, &rect_bg);
    }

    std::string player_information(int id, const Vector2& pos, const Vector2& vel)
    {
        std::string str = std::to_string(id) + ";"
            + pos.Vtos() + ";" + vel.Vtos() + ";";
        return str;
    }

};

#endif