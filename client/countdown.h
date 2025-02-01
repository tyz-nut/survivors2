#ifndef _COUNTDOWN_H_
#define _COUNTDOWN_H_

#include "timer.h"
#include "util.h"
#include "camera.h"
#include "resources_manager.h"

class Countdown
{
public:
    Countdown()
    {
        //预备时间初始化
        timer_countdown.set_one_shot(false);
        timer_countdown.set_wait_time(1.0f);
        timer_countdown.set_on_timeout([&]()
            {
                val_countdown--;
                switch (val_countdown)
                {
                case 3:play_audio(_T("ui_3")); break;
                case 2:play_audio(_T("ui_2")); break;
                case 1:play_audio(_T("ui_1")); break;
                case 0:play_audio(_T("ui_fight")); break;
                case -1:
                    Event2::instance()->is_ready = true;
                    break;
                }
            });

        img_ui_1 = ResourcesManager::instance()->find_image("ui_1");
        img_ui_2 = ResourcesManager::instance()->find_image("ui_2");
        img_ui_3 = ResourcesManager::instance()->find_image("ui_3");
    }
    ~Countdown() = default;

    void on_update(float delta)
    {
        timer_countdown.on_update(delta);
    }

    void on_render(Camera& camera)
    {
        //绘制倒计时
        switch (val_countdown)
        {
        case 3:
        {
            static const Rect rect_ui_3 =
            {
                1280 / 2 - img_ui_3->getwidth() / 2,
                720 / 2 - img_ui_3->getheight() / 2,
                img_ui_3->getwidth(), img_ui_3->getheight()
            };
            putimage_ex(camera, img_ui_3, &rect_ui_3);
        }
        break;
        case 2:
        {
            static const Rect rect_ui_2 =
            {
                1280 / 2 - img_ui_2->getwidth() / 2,
                720 / 2 - img_ui_2->getheight() / 2,
                img_ui_2->getwidth(), img_ui_2->getheight()
            };
            putimage_ex(camera, img_ui_2, &rect_ui_2);
        }
        break;
        case 1:
        {
            static const Rect rect_ui_1 =
            {
                1280 / 2 - img_ui_1->getwidth() / 2,
                720 / 2 - img_ui_1->getheight() / 2,
                img_ui_1->getwidth(), img_ui_1->getheight()
            };
            putimage_ex(camera, img_ui_1, &rect_ui_1);
        }
        break;
        default: break;
        }
    }

private:
    Timer timer_countdown;               //倒计时计时器
    int val_countdown = 4;				//起跑倒计时

    IMAGE* img_ui_1;
    IMAGE* img_ui_2;
    IMAGE* img_ui_3;
};

#endif