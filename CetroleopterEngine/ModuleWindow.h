#ifndef __ModuleWindow_H__
#define __ModuleWindow_H__

#include "Module.h"
#include "SDL/include/SDL.h"


class Application;

class ModuleWindow : public Module
{
public:

	ModuleWindow(bool start_enabled = true);

	// Destructor
	virtual ~ModuleWindow();

	bool Init();
	update_status PreUpdate(float dt);
	bool CleanUp();

	void SetTitle(const char* title);

	float GetBrightness()const;
	void SetBrightness(float value);

	void GetWindowsSize(SDL_Window* window, int& width, int& height);
	void SetWindowSize(uint width, uint height);

	bool GetFullscreen();
	void SetFullscreen(bool result);

	bool GetResizable();
	void SetResizable(bool result);

	bool GetBorderless();
	void SetBorderless(bool result);

	bool GetFullscreenDesktop();
	void SetFullscreenDesktop(bool result);

	int GetHeight();
	int GetWidth();

	void UpdateWindow();

public:
	//The window we'll be rendering to
	SDL_Window* window;

	//The surface contained by the window
	SDL_Surface* screen_surface;

public:

	bool fullscreen = false;
	bool resizable = true;
	bool borderless = false;
	bool fullscreenDesktop = false;

	Uint32 flags;
	int width;
	int height;
	
};

#endif // __ModuleWindow_H__