#ifndef _SCENE_MANAGER_H_
#define _SCENE_MANAGER_H_

#include "scene.h"

extern Scene* menu_scene;
extern Scene* game_scene;
extern Scene* waiting_scene;

class SceneManager
{
public:
    enum class SceneType
    {
        Menu,
        Waiting,
        Game,
    };

public:
    static SceneManager* instance();

    void scene_init();

    void set_current_scene(Scene* scene);

    void switch_to(SceneType type);

    void on_update(float delta)
    {
        current_scene->on_update(delta);
    }

    void on_render()
    {
        current_scene->on_render();
    }

    void on_input(const ExMessage& msg)
    {
        current_scene->on_input(msg);
    }

private:
    static SceneManager* manager;
    Scene* current_scene = nullptr;

private:
    SceneManager() = default;
    ~SceneManager() = default;
};

#endif