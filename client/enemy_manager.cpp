#include "enemy_manager.h"

EnemyManager* EnemyManager::manager = nullptr;

EnemyManager* EnemyManager::instance()
{
    if (!manager)
    {
        manager = new EnemyManager();
    }

    return manager;
}

void EnemyManager::enemy_on_game(const Map& map)
{
    this->map = map;
    
    timer_Spawnedge.set_wait_time(this->map.enemy_pig_spawnl_interva);
    timer_Spawnedge.set_one_shot(false);
    timer_Spawnedge.set_on_timeout([&]()
        {
            Vector2 position;
            Spawnedge edge = (Spawnedge)(rand() % 4);
            switch (edge)
            {
            case Spawnedge::Up:
                position.x = float(rand() % (int)this->map.area.x);
                position.y = -80;
                break;
            case Spawnedge::Down:
                position.x = rand() % (int)this->map.area.x;
                position.y = -80;
                break;
            case Spawnedge::Left:
                position.x = -80;
                position.y = rand() % (int)this->map.area.y;
                break;
            case Spawnedge::Right:
                position.x = -map.area.x;
                position.y = rand() % (int)this->map.area.x;
                break;
            }
            if(enemy_pig_num <= this->map.enemy_pig_max_num)
            {
                Enemy* enemy = new EnemyPig();
                enemy->set_position(position);
                enemy->set_move_range(map.area);
                enemy->reset_current_anim();
                enemy->reset_hp();
                enemys.push_back(enemy);
            }
        });

    
}

void EnemyManager::reset_hp()
{
    for (int i = 0; i < enemys.size(); i++)
    {
        enemys[i]->reset_hp();
    }
}

void EnemyManager::reset_current_anim()
{
    for (auto itor : enemys)
    {
        itor->reset_current_anim();
    }
}

void EnemyManager::set_move_range(const Vector2& area)
{
    for (auto itor : enemys)
    {
        itor->set_move_range(area);
    }
}

//void EnemyManager::set_enemys_position(std::vector<Vector2>& positions)
//{
//    for (size_t i = 0; i < enemys.size(); i++)
//    {
//        if (enemy_self->get_id() == i)
//            continue;
//        enemys[i]->set_position(positions[i]);
//    }
//}
//
//void EnemyManager::set_enemys_velocity(std::vector<Vector2>& velocitys)
//{
//    for (size_t i = 0; i < enemys.size(); i++)
//    {
//        if (enemy_self->get_id() == i)
//            continue;
//        enemys[i]->set_position(velocitys[i]);
//    }
//}

Enemy* EnemyManager::set_enemyType(Enemy* enemy, EnemyManager::EnemyType type)
{
    switch (type)
    {
    case EnemyManager::EnemyType::pig:
        Enemy* enemy_set = new EnemyPig();
        delete enemy;
        return enemy_set;
        break;
        /*case EnemyManager::EnemyType::manbo:
            Enemy* enemy_set = new EnemyManbo();
            enemy_set->set_id(enemy->get_id());
            delete enemy;
            return enemy_set;
            break;
        case EnemyManager::EnemyType::paimeng:
            Enemy* enemy_set = new EnemyPaimeng();
            enemy_set->set_id(enemy->get_id());
            delete enemy;
            return enemy_set;
            break;*/
    }
}

void EnemyManager::on_update(float delta)
{
    timer_Spawnedge.on_update(delta);
    for (size_t i = 0; i < enemys.size(); i++)
        enemys[i]->on_update(delta);
}

void EnemyManager::on_render(const Camera& camera)
{
    for (size_t i = 0; i < enemys.size(); i++)
        enemys[i]->on_render(camera);
}
