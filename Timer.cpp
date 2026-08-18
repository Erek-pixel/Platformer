#include "Timer.hpp"

void Timer::update(float dt)
{
	if (is_counting)
		time -= dt;
	if (!time_up && time <= 0.f)
	{
		time_up = true;
		is_counting = false;
	}
}

void Timer::stop()
{
	is_counting = false;
}

void Timer::start()
{
	is_counting = true;
}

void Timer::restart()
{
	time_up = false;
	time = max_time;
	start();
}

void Timer::reset()
{
	time_up = false;
	time = max_time;
	stop();
}