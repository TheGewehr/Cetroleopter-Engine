// ----------------------------------------------------
// Timer.cpp
// Body for CPU Tick Timer class
// ----------------------------------------------------

#include "Timer.h"

// ---------------------------------------------
Timer::Timer()
{
	Start();
}

// ---------------------------------------------
void Timer::Start()
{
	reset = false;
	paused = false;
	running = true;
	started_at = SDL_GetTicks();
}

// ---------------------------------------------
void Timer::Reset()
{
	started_at = 0;
	paused_at = 0;
	resumed_at = 0;
	stopped_at = 0;

	reset = true;
	paused = false;
	running = false;
	stopped_at = SDL_GetTicks();
}

void Timer::Pause()
{
	reset = false;
	paused = true;
	running = false;
	paused_at = SDL_GetTicks() - started_at;
}

void Timer::Resume()
{
	reset = false;
	paused = false;
	running = true;
	resumed_at = paused_at;
}

float Timer::PauseRetSeconds()
{
	reset = false;
	paused = true;
	running = false;
	paused_at = SDL_GetTicks() - started_at;

	return float(SDL_GetTicks() - paused_at) / 1000.0f;
}

float Timer::ResumeRetSeconds()
{
	reset = false;
	paused = false;
	running = true;
	resumed_at = paused_at;

	return float(SDL_GetTicks() - started_at) / 1000.0f;;
}

// ---------------------------------------------
Uint32 Timer::Read()
{
	if(running == true)
	{
		return SDL_GetTicks() - started_at;
	}
	else
	{
		return stopped_at - started_at;
	}
}


float Timer::ReadSec() const
{
	if (!reset)
	{
		if (running == true)
			return float(SDL_GetTicks() - started_at) / 1000.0f;
		else
			return 0;
	}
	else
		return 0;
}

