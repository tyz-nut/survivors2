#include "scene_manager.h"

SceneManager* SceneManager::manager = nullptr;

SceneManager* SceneManager::instance()
{
    if (!manager)
    {
        manager = new SceneManager();
    }

    return manager;
}

void SceneManager::scene_init()
{
    SceneManager::set_current_scene(menu_scene);
}

void SceneManager::set_current_scene(Scene* scene)
{
    current_scene = scene;
    current_scene->on_enter();
}

void SceneManager::switch_to(SceneManager::SceneType type)
{
    current_scene->on_exit();
    switch (type)
    {
    case SceneType::Menu:
        current_scene = menu_scene;
        break;
    case SceneType::Waiting:
        current_scene = waiting_scene;
        break;
    case SceneType::Game:
        current_scene = game_scene;
        break;
    default:
        break;
    }
    current_scene->on_enter();
}