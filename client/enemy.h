#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "animation.h"
#include "resources_manager.h"
#include "collision_manager.h"

class Enemy
{
public:
    enum class Facing
    {
        Up, Down, Left, Right
    };
public:
    Enemy()
    {
        hit_box = CollisionManager::instance()->create_collision_box();
        hurt_box = CollisionManager::instance()->create_collision_box();
    }

    ~Enemy()
    {
        CollisionManager::instance()->destroy_collision_box(hit_box);
        CollisionManager::instance()->destroy_collision_box(hurt_box);
    }

    virtual void on_update(float delta){}

    virtual void on_render(const Camera& camera)
    {
        if (!current_anim) return;
        current_anim->on_render(camera);
    }

    virtual void reset_current_anim() {}

    void set_position(const Vector2& position)
    {
        this->position = position;
    }

    const Vector2& get_position() const
    {
        //获得敌人位置//
        return position;
    }

    void set_velocity(Vector2 velocity)
    {
        this->velocity = velocity;
    }

    const Vector2& get_velocity() const
    {
        return velocity;
    }

    void set_hp(int enemy_hp)
    {
        this->enemy_hp = enemy_hp;
    }

    const int get_hp() const
    {
        return enemy_hp;
    }

    virtual void reset_hp() {}

    void set_target_position(const Vector2 position)
    {
        this->target_position = position;
    }

    void set_move_range(const Vector2& bk)
    {
        background = bk;
    }

    void Hurt()
    {
        alive = false;
    }

    bool CheckAlive()
    {
        return alive;
    }

private:
    const int ENEMY_WIDTH = 80;
    const int ENEMY_HEIGHT = 80;
    const int SHADOW_WIDTH = 48;

protected:
    int enemy_hp = 1;
    Vector2 position;
    Vector2 target_position;
    Vector2 velocity;
    Vector2 background;
    Animation* current_anim = nullptr;
    bool facing_left = false;
    bool alive = true;
    CollisionBox* hit_box = nullptr;
    CollisionBox* hurt_box = nullptr;
};

#endif