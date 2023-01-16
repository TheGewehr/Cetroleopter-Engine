#ifndef __TIMER_H__
#define __TIMER_H__

#include "Globals.h"
#include "SDL\include\SDL.h"

class Timer
{
public:

	// Constructor
	Timer();

	void Start();
	void Reset();

	void Pause();
	void Resume();

	float PauseRetSeconds();
	float ResumeRetSeconds();

	Uint32 Read();
	float ReadSec() const;

public:

	bool	running;
	bool	reset = false;
	bool	paused = false;
	
	Uint32	started_at;
	Uint32  paused_at;
	Uint32  resumed_at;
	Uint32	stopped_at;
};

#endif //__TIMER_H__