#include "player_manager.h"

PlayerManager* PlayerManager::manager = nullptr;

PlayerManager* PlayerManager::instance()
{
    if (!manager)
    {
        manager = new PlayerManager();
    }

    return manager;
}

void PlayerManager::player_init()
{
    for (int i = 0; i < player_max_num; i++)
    {
        Player* player = new PlayerHajimi();
        player->set_id(i);
        players.push_back(player);
    }
}

void PlayerManager::player_on_game(const Map& map)
{
    reset_position(map.player_position);
    set_move_range(map.area);
    reset_current_anim();
    reset_hp();
}

void PlayerManager::reset_position(const Vector2& position)
{
    for (int i = 0; i < players.size(); i++)
    {
        players[i]->set_position(position);
    }
}

void PlayerManager::reset_hp()
{
    for (int i = 0; i < players.size(); i++)
    {
        players[i]->reset_hp();
    }
}

void PlayerManager::reset_current_anim()
{
    for (auto itor : players)
    {
        itor->reset_current_anim();
    }
}

void PlayerManager::set_move_range(const Vector2& area)
{
    for (auto itor : players)
    {
        itor->set_move_range(area);
    }
}

const Vector2& PlayerManager::get_self_position()
{
    return player_self->get_position();
}

const Vector2& PlayerManager::get_self_velocity()
{
    return player_self->get_velocity();
}

//void PlayerManager::set_players_position(std::vector<Vector2>& positions)
//{
//    for (size_t i = 0; i < players.size(); i++)
//    {
//        if (player_self->get_id() == i)
//            continue;
//        players[i]->set_position(positions[i]);
//    }
//}
//
//void PlayerManager::set_players_velocity(std::vector<Vector2>& velocitys)
//{
//    for (size_t i = 0; i < players.size(); i++)
//    {
//        if (player_self->get_id() == i)
//            continue;
//        players[i]->set_position(velocitys[i]);
//    }
//}

Player* PlayerManager::set_playerType(Player* player, PlayerManager::PlayerType type)
{
    switch (type)
    {
    case PlayerManager::PlayerType::hajimi:
        Player* player_set = new PlayerHajimi();
        player_set->set_id(player->get_id());
        delete player;
        return player_set;
        break;
    /*case PlayerManager::PlayerType::manbo:
        Player* player_set = new PlayerManbo();
        player_set->set_id(player->get_id());
        delete player;
        return player_set;
        break;
    case PlayerManager::PlayerType::paimeng:
        Player* player_set = new PlayerPaimeng();
        player_set->set_id(player->get_id());
        delete player;
        return player_set;
        break;*/
    }
}

void PlayerManager::on_update(float delta)
{
    for (size_t i = 0; i < players.size(); i++)
        players[i]->on_update(delta);
}

void PlayerManager::on_render(const Camera& camera)
{
    for (size_t i = 0; i < players.size(); i++)
        players[i]->on_render(camera);
}

void PlayerManager::on_input(const ExMessage& msg)
{
    player_self->on_input(msg);
}