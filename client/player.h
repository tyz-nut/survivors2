#ifndef _PLAYER__H_
#define _PLAYER__H_

extern const int window_width;
extern const int window_height;

#include "animation.h"
#include "resources_manager.h"

class Player
{
public:
	enum class Facing
	{
		Up, Down, Left, Right
	};

public:
	Player() = default;
	~Player() = default;

    virtual void on_input(const ExMessage& msg)
    {
        switch (msg.message)
        {
        case WM_KEYDOWN:
            switch (msg.vkcode)
            {
            case 0x41:  //A
            case VK_LEFT:
                is_move_left = true;
                break;
            case 0x44:  //D
            case VK_RIGHT:
                is_move_right = true;
                break;
            case 0x57:  //W
                is_move_up = true;
                break;
            case 0x53:  //S
                is_move_down = true;
                break;
            }
            break;
        case WM_KEYUP:
            switch (msg.vkcode)
            {
            case 0x41:  //A
            case VK_LEFT:
                is_move_left = false;
                break;
            case 0x44:  //D
            case VK_RIGHT:
                is_move_right = false;
                break;
            case 0x57:  //W
                is_move_up = false;
                break;
            case 0x53:  //S
                is_move_down = false;
            }
            break;
        }
    }

	virtual void on_update(float delta)
	{
		if (can_control)
		{
			int dir_x = is_move_right - is_move_left;
			int dir_y = is_move_down - is_move_up;
			Vector2 dir = Vector2((float)dir_x, (float)dir_y);
			velocity = dir.normalize() * SPEED_RUN;
			position += velocity * delta;
		}
		else
		{
			position += velocity * delta;
		}

		//»ÀŒÔ“∆∂Ø∑∂Œß//
		if (position.x < window_width / 2.0f) position.x = window_width / 2.0f;
		if (position.y < window_height / 2.0f) position.y = window_height / 2.0f;
		if (position.x + 96 > background.x - window_width / 2.0f) position.x = background.x - window_width / 2.0f - 96;
		if (position.y + 96 > background.y - window_height / 2.0f) position.y = background.y - window_height / 2.0f - 96;
	}

	virtual void on_render(const Camera& camera)
	{
		if (!current_anim) return;
		current_anim->on_render(camera);
	}

	virtual void reset_current_anim(){}

	void set_position(const Vector2& position)
	{
		this->position = position;
	}

	const Vector2& get_position() const
	{
		return position;
	}

	void set_velocity(Vector2 velocity)
	{
		this->velocity = velocity;
	}

	const Vector2& get_velocity()
	{
		return velocity;
	}

	void set_id(int player_id)
	{
		this->player_id = player_id;
	}

	const int get_id()
	{
		return player_id;
	}

	void set_can_control()
	{
		can_control = true;
	}

	void set_move_range(const Vector2& bk)
	{
		background = bk;
	}

protected:
	const float SPEED_RUN = 200.0f;
	int player_id = -1;
	bool can_control = false;

	bool is_move_right = false;
	bool is_move_up = false;
	bool is_move_down = false;
	bool is_move_left = false;
	bool is_attack = false;

protected:
	Vector2 position;
	Vector2 velocity;
	Vector2 background;
	Animation* current_anim = nullptr;
};

#endif // !_PLAYER_H_
