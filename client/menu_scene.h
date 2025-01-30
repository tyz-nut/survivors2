#ifndef _MENU_SCENE_H_
#define _MENU_SCENE_H_

#define CENTER true

#include "scene.h"
#include "scene_manager.h"
#include "resources_manager.h"
#include "camera.h"
#include "button.h"



class MenuScene : public Scene
{
public:
    MenuScene() = default;
    ~MenuScene() = default;

    void on_enter()
    {
        img_menu_background = ResourcesManager::instance()->find_image("menu");
        start_game_button.set_position(Vector2(0, 430), CENTER);
        quit_game_button.set_position(Vector2(0, 550), CENTER);
    }

    void on_render()
    {
        putimage(0, 0, img_menu_background);
        start_game_button.render();
        quit_game_button.render();
    }

    void on_update(float delta)
    {
        if (Event2::instance()->is_game_start)
            SceneManager::instance()->switch_to(SceneManager::SceneType::Waiting);
    }

    void on_input(const ExMessage& msg)
    {
        quit_game_button.on_input(msg);
        start_game_button.on_input(msg);
    }

private:
    IMAGE* img_menu_background;
    StartGameButton start_game_button;
    QuitGameButton quit_game_button;
};

#endif