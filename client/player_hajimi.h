#ifndef _PLAYER_HAJIMI_H_
#define _PLAYER_HAJIMI_H_

#include "player.h"

class PlayerHajimi : public Player
{
public:
	PlayerHajimi()
	{
		timer_invulnerable_status.set_wait_time(1.0f);
		timer_invulnerable_status.set_one_shot(true);
		timer_invulnerable_status.set_on_timeout([&]()
			{
				is_invulnerable = false;
			});

		timer_invulnerable_blink.set_wait_time(0.075f);
		timer_invulnerable_blink.set_one_shot(false);
		timer_invulnerable_blink.set_on_timeout([&]()
			{
				is_blink_invisible = !is_blink_invisible;
			});

		anim_idle_up.set_loop(true);
		anim_idle_up.set_interval(0.1f);
		anim_idle_up.add_frame(ResourcesManager::instance()->find_atlas("hajimi_idle_up"));

		anim_idle_down.set_loop(true);
		anim_idle_down.set_interval(0.1f);
		anim_idle_down.add_frame(ResourcesManager::instance()->find_atlas("hajimi_idle_down"));

		anim_idle_left.set_loop(true);
		anim_idle_left.set_interval(0.1f);
		anim_idle_left.add_frame(ResourcesManager::instance()->find_atlas("hajimi_idle_left"));

		anim_idle_right.set_loop(true);
		anim_idle_right.set_interval(0.1f);
		anim_idle_right.add_frame(ResourcesManager::instance()->find_atlas("hajimi_idle_right"));

		anim_run_up.set_loop(true);
		anim_run_up.set_interval(0.1f);
		anim_run_up.add_frame(ResourcesManager::instance()->find_atlas("hajimi_run_up"));

		anim_run_down.set_loop(true);
		anim_run_down.set_interval(0.1f);
		anim_run_down.add_frame(ResourcesManager::instance()->find_atlas("hajimi_run_down"));

		anim_run_left.set_loop(true);
		anim_run_left.set_interval(0.1f);
		anim_run_left.add_frame(ResourcesManager::instance()->find_atlas("hajimi_run_left"));

		anim_run_right.set_loop(true);
		anim_run_right.set_interval(0.1f);
		anim_run_right.add_frame(ResourcesManager::instance()->find_atlas("hajimi_run_right"));

	}
	~PlayerHajimi() = default;

	void on_input(const ExMessage& msg)
	{
		Player::on_input(msg);
	}

	void on_update(float delta)
	{
		Player::on_update(delta);

		if (velocity.approx(Vector2(0, 0)))
		{
			switch (facing)
			{
			case Player::Facing::Up:
				current_anim = &anim_idle_up;
				break;
			case Player::Facing::Down:
				current_anim = &anim_idle_down;
				break;
			case Player::Facing::Left:
				current_anim = &anim_idle_left;
				break;
			case Player::Facing::Right:
				current_anim = &anim_idle_right;
				break;
			}
		}
		else
		{
			if (abs(velocity.y) >= 0.0001f)
				facing = (velocity.y > 0) ? Player::Facing::Down : Player::Facing::Up;
			if (abs(velocity.x) >= 0.0001f)
				facing = (velocity.x > 0) ? Player::Facing::Right : Player::Facing::Left;

			switch (facing)
			{
			case Player::Facing::Up:
				current_anim = &anim_run_up;
				break;
			case Player::Facing::Down:
				current_anim = &anim_run_down;
				break;
			case Player::Facing::Left:
				current_anim = &anim_run_left;
				break;
			case Player::Facing::Right:
				current_anim = &anim_run_right;
				break;
			}
		}

		if (!current_anim) return;
		current_anim->set_position(position);
		current_anim->on_update(delta);
	}

	void on_render(const Camera& camera)
	{
		Player::on_render(camera);
	}

	void reset_current_anim()
	{
		this->current_anim = &anim_idle_down;
	}

	void reset_hp()
	{
		player_hp = 10;
	}

private:
	Animation anim_idle_up;
	Animation anim_idle_down;
	Animation anim_idle_left;
	Animation anim_idle_right;
	Animation anim_run_up;
	Animation anim_run_down;
	Animation anim_run_left;
	Animation anim_run_right;

	Facing facing = Facing::Down;
};

#endif // !_PLAYER_HAJIMI_H_
