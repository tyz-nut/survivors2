#ifndef _ENEMY_MANAGER_H_
#define _ENEMY_MANAGER_H_

#include "enemy.h"
#include "player.h"
#include "enemy_pig.h"
#include "map_manager.h"

#include <vector>

extern std::vector<Enemy*> enemys;
extern std::vector<Player*> players;
extern const int window_width;
extern const int window_height;

class EnemyManager
{
public:
    enum class Spawnedge
    {
        Up, Down, Left, Right,
    };

    enum class EnemyType
    {
        pig,
    };

public:
    static EnemyManager* instance();

    void enemy_init();

    void enemy_on_game(const Map& map);

    void reset_hp();

    void reset_current_anim();

    void set_move_range(const Vector2& area);

    void set_target_position(const Vector2& position);

    /*void set_players_position(std::vector<Vector2>& positions);

    void set_players_velocity(std::vector<Vector2>& velocitys);*/

    Enemy* set_enemyType(Enemy* enemy, EnemyType type);

    void on_update(float delta);

    void on_render(const Camera& camera);

private:
    static EnemyManager* manager;
    Map map;
    int enemy_pig_num = 0;
    Timer timer_Spawnedge;

private:
    EnemyManager() = default;
    ~EnemyManager() = default;
};

#endif