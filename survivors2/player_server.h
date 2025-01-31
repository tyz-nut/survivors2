#ifndef _PLAYER_SERVER_H_
#define _PLAYER_SERVER_H_

#include "../client/vector2.h"

class PlayerServer
{
public:

public:
	PlayerServer() = default;
	~PlayerServer() = default;

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

	const Vector2& get_velocity() const
	{
		return velocity;
	}

	void set_id(int player_id)
	{
		this->player_id = player_id;
	}

	int get_id() const
	{
		return player_id;
	}

	void set_hp(int hp)
	{
		this->hp = hp;
	}

	int get_hp() const
	{
		return hp;
	}

protected:
	const float SPEED_RUN = 5.0f;
	int player_id = 0;
	int hp = 10;
	bool is_attck = false;
	bool is_skill1 = false;
	bool is_skill2 = false;

protected:
	Vector2 position;
	Vector2 velocity;
};

#endif // !_PLAYER_H_
