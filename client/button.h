#ifndef _BUTTON_
#define _BUTTON_

#include "vector2.h"
#include "resources_manager.h"
#include "event2.h"

extern const int window_width;
extern const int window_height;

class Button
{
public:
    enum class Status {
        Idle = 0, 
        Hovered, 
        Pushed 
    };

public:
    Button() = default;
    ~Button() = default;

    void on_input(const ExMessage& msg)
    {
        switch (msg.message)
        {
        case WM_MOUSEMOVE:
            if (status == Status::Idle && CheckCursorHit(msg.x, msg.y))
                status = Status::Hovered;
            else if (status == Status::Hovered && !CheckCursorHit(msg.x, msg.y))
                status = Status::Idle;
            break;
        case WM_LBUTTONDOWN:
            if (CheckCursorHit(msg.x, msg.y))
                status = Status::Pushed;
            break;
        case WM_LBUTTONUP:
            if (status == Status::Pushed)
                OnClick();
            break;
        default:
            break;
        }
    }

    void set_position(Vector2 position, bool is_center = false)
    {
        if (is_center == false)
            this->position = position;
        else
        {
            this->position.y = position.y;
            this->position.x = (1280 - area.x) / 2;
        }
    }

    void render()
    {
        switch (status)
        {
        case Status::Idle:
            putimage((int)position.x, (int)position.y, img_idle);
            break;
        case Status::Hovered:
            putimage((int)position.x, (int)position.y, img_hovered);
            break;
        case Status::Pushed:
            putimage((int)position.x, (int)position.y, img_pushed);
            break;
        }
    }

protected:
    Vector2 position = { 0 ,0 };
    Vector2 area = { 0, 0 };
    IMAGE* img_idle = nullptr;
    IMAGE* img_hovered = nullptr;
    IMAGE* img_pushed = nullptr;
    Status status = Status::Idle;

protected:
    //¼ì²âÊó±êµã»÷//
    bool CheckCursorHit(int x, int y)
    {
        return x >= position.x && x <= position.x + area.x && y >= position.y && y <= position.y + area.y;
    }

    virtual void OnClick() = 0;
};


class StartGameButton : public Button
{
public:
    StartGameButton()
    {
        this->img_idle = ResourcesManager::instance()->find_image("ui_start_idle");
        this->img_hovered = ResourcesManager::instance()->find_image("ui_start_hovered");
        this->img_pushed = ResourcesManager::instance()->find_image("ui_start_pushed");
        area.x = (float)img_idle->getwidth();
        area.y = (float)img_idle->getheight();
    }
    ~StartGameButton() = default;

protected:
    void OnClick()
    {
        Event2::instance()->is_game_start = true;
    }
};

class QuitGameButton : public Button
{
public:
    QuitGameButton()
    {
        this->img_idle = ResourcesManager::instance()->find_image("ui_quit_idle");
        this->img_hovered = ResourcesManager::instance()->find_image("ui_quit_hovered");
        this->img_pushed = ResourcesManager::instance()->find_image("ui_quit_pushed");
        area.x = (float)img_idle->getwidth();
        area.y = (float)img_idle->getheight();
    }
    ~QuitGameButton() = default;

protected:
    void OnClick()
    {
        Event2::instance()->is_quit = true;
    }
};

#endif // !_BUTTON_