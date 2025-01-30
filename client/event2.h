#ifndef _EVENT_2_
#define _EVENT_2_

class Event2
{
public:
	static Event2* instance();

public:
	bool is_quit = false;
	bool is_game_start = false;

	bool is_connect = false;
	bool is_matched = false;

	bool is_ready = false;
	bool is_game_over = false;

private:
	static Event2* manager;

private:
	Event2() = default;
	~Event2() = default;
};

Event2* Event2::manager = nullptr;

Event2* Event2::instance()
{
	if (!manager)
	{
		manager = new Event2();
	}

	return manager;
}

#endif