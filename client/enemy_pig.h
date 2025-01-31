#ifndef _ENEMY_PIG_H_
#define _ENEMY_PIG_H_

#include "enemy.h"

class EnemyPig : public Enemy
{
public:
    EnemyPig()
    {
        anim_run_left.set_loop(true);
        anim_run_left.set_interval(0.1f);
        anim_run_left.add_frame(ResourcesManager::instance()->find_atlas("pig_left"));

        anim_run_right.set_loop(true);
        anim_run_right.set_interval(0.1f);
        anim_run_right.add_frame(ResourcesManager::instance()->find_atlas("pig_right"));

        img_shadow = ResourcesManager::instance()->find_image("shadow_pig");
    }
    ~EnemyPig() = default;

    void on_update(float delta)
    {
        int dir_x = target_position.x - position.x;
        int dir_y = target_position.y - position.y;
        Vector2 dir = Vector2((float)dir_x, (float)dir_y).normalize();
        velocity = dir * SPEED_RUN;
        position += velocity * delta;

        if (abs(velocity.x) >= 0.0001f)
            facing = (velocity.x > 0) ? Facing::Right : Facing::Left;

        switch (facing)
        {
        case Facing::Left:
            current_anim = &anim_run_left;
            break;
        case Facing::Right:
            current_anim = &anim_run_right;
            break;
        }

        if (!current_anim) return;
        current_anim->set_position(position);
        current_anim->on_update(delta);
    }

    void on_render(const Camera& camera)
    {
        static const Rect rect_shadow =
        {
            position.x + (ENEMY_WIDTH / 2 - SHADOW_WIDTH / 2),
            position.y + ENEMY_HEIGHT - 35,
            img_shadow->getwidth(), img_shadow->getheight()
        };
        putimage_ex(camera, img_shadow, &rect_shadow);


        Enemy::on_render(camera);
    }

    void reset_current_anim()
    {
        this->current_anim = &anim_run_right;
    }

    void reset_hp()
    {
        enemy_hp = 10;
    }

private:
    Animation anim_run_left;
    Animation anim_run_right;
    IMAGE* img_shadow;

    Facing facing = Facing::Right;

    const int ENEMY_WIDTH = 80;
    const int ENEMY_HEIGHT = 80;
    const int SHADOW_WIDTH = 48;

private:
    const int SPEED_RUN = 20;
    bool facing_left = false;
    bool alive = true;
};

#endif