#ifndef _PLAYER_MANAGER_H_
#define _PLAYER_MANAGER_H_

#include "player.h"
#include "player_hajimi.h"
#include "player_manbo.h"
#include "player_paimeng.h"

#include <vector>

extern Player* player_self;
extern std::vector<Player*> players;
extern const int window_width;
extern const int window_height;
extern const int player_max_num;

class PlayerManager
{
public:
    enum class PlayerType
    {
        hajimi,
        manbo,
        paimeng,
    };

public:
    static PlayerManager* instance();

    void player_init();

    void reset_position(const Vector2& background);

    void reset_current_anim();

    void set_move_range(const Vector2 background);

    const Vector2& get_self_position();

    const Vector2& get_self_velocity();

    void set_players_position(std::vector<Vector2>& positions);

    void set_players_velocity(std::vector<Vector2>& velocitys);

    Player* set_playerType(Player* player, PlayerType type);

    void on_update(float delta);

    void on_render(const Camera& camera);

    void on_input(const ExMessage& msg);

private:
    static PlayerManager* manager;

private:
    PlayerManager() = default;
    ~PlayerManager() = default;
};

#endif