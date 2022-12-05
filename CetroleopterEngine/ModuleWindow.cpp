#include "ModuleWindow.h"
#include "Globals.h"
#include "Application.h"


//#include "imgui/imgui.h"
////#include "imgui/imgui_impl_glfw.h"  // CON EL GLEW? <- ????
//#include "imgui/imgui_impl_opengl3.h"



ModuleWindow::ModuleWindow(bool start_enabled) : Module(start_enabled)
{
	window = NULL;
	screen_surface = NULL;
}

// Destructor
ModuleWindow::~ModuleWindow()
{
}

// Called before render is available
bool ModuleWindow::Init()
{
	LOG("Init SDL window & surface");
	bool ret = true;

	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		LOG("SDL_VIDEO could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}
	else
	{
		//Create window
		width = SCREEN_WIDTH * SCREEN_SIZE;
		height = SCREEN_HEIGHT * SCREEN_SIZE;
		flags = SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN;

		//Use OpenGL 2.1
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

		if(WIN_FULLSCREEN == true)
		{
			flags |= SDL_WINDOW_FULLSCREEN;
		}

		if(WIN_RESIZABLE == true)
		{
			flags |= SDL_WINDOW_RESIZABLE;
		}

		if(WIN_BORDERLESS == true)
		{
			flags |= SDL_WINDOW_BORDERLESS;
		}

		if(WIN_FULLSCREEN_DESKTOP == true)
		{
			flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
		}

		window = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, flags);		

		if(window == NULL)
		{
			LOG("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			ret = false;
		}
		else
		{
			//Get window surface
			screen_surface = SDL_GetWindowSurface(window);

			SDL_Surface* icon = SDL_LoadBMP("icon.bmp");
			if (icon != nullptr)
			{
				SDL_SetWindowIcon(window, icon);
				SDL_FreeSurface(icon);
			}
		}
	}


	//IMGUI_CHECKVERSION();
	//ImGui::CreateContext();
	//ImGuiIO& io = ImGui::GetIO(); (void)io;
	//ImGui::StyleColorsDark();
	////ImGui_ImplGlfw_InitForOpenGL(window, true); // GLEW ?????
	//ImGui_ImplOpenGL3_Init("#version 330");


	return ret;
}

update_status ModuleWindow::PreUpdate(float dt)
{
	if (fullscreen)
	{
		flags |= SDL_WINDOW_FULLSCREEN;
	}
	else
	{
		flags != SDL_WINDOW_FULLSCREEN;
	}

	if (resizable)
	{
		flags |= SDL_WINDOW_RESIZABLE;
	}
	else
	{
		flags != SDL_WINDOW_RESIZABLE;
	}

	if (borderless)
	{
		flags |= SDL_WINDOW_BORDERLESS;
	}
	else
	{
		flags != SDL_WINDOW_BORDERLESS;
	}

	if (fullscreenDesktop)
	{
		flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
	}
	else
	{
		flags != SDL_WINDOW_FULLSCREEN_DESKTOP;
	}
	
	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleWindow::CleanUp()
{
	LOG("Destroying SDL window and quitting all SDL systems");

	//Destroy window
	if(window != NULL)
	{
		SDL_DestroyWindow(window);
		//glfwDestroyWindow(window); // GLEW ?????
		//glfwTerminate(); // GLEW ?????

	}

	

	// Quit ImGui for OpenGL3
	//ImGui_ImplOpenGL3_Shutdown();
	//ImGui_ImplGlfw_Shutdown(); // GLEW ?????
	//ImGui::DestroyContext();

	//Quit SDL subsystems
	SDL_Quit();
	return true;
}

void ModuleWindow::SetTitle(const char* title)
{
	SDL_SetWindowTitle(window, title);
}

float ModuleWindow::GetBrightness() const
{
	return SDL_GetWindowBrightness(window);
}

void ModuleWindow::SetBrightness(float value)
{
	int result = SDL_SetWindowBrightness(window, value);                                                

	if (result != 0)
	{
		LOG("[ERROR] SDL_SetWindowBrightness() failed! SDL_Error: %s", SDL_GetError());
	}
}

void ModuleWindow::GetWindowsSize(SDL_Window* window, int& _width, int& _height)
{
	
	SDL_GetWindowSize(window, &_width, &_height);
}

void ModuleWindow::SetWindowSize(uint _width, uint _height)
{
	width = _width;
	height = _height;
	SDL_SetWindowSize(window, width, height);
}

bool ModuleWindow::GetFullscreen()
{
	return fullscreen;
}

void ModuleWindow::SetFullscreen(bool result)
{
	fullscreen = result;
}

bool ModuleWindow::GetResizable()
{
	return resizable;
}

void ModuleWindow::SetResizable(bool result)
{
	resizable = result;
}

bool ModuleWindow::GetBorderless()
{
	return borderless;
}

void ModuleWindow::SetBorderless(bool result)
{
	borderless = result;
}

bool ModuleWindow::GetFullscreenDesktop()
{
	return fullscreenDesktop;
}

void ModuleWindow::SetFullscreenDesktop(bool result)
{
	fullscreenDesktop = result;
}

int ModuleWindow::GetHeight()
{
	return height;
}

int ModuleWindow::GetWidth()
{
	return width;
}

void ModuleWindow::UpdateWindow()
{
	if (window != NULL)
	{
		SDL_DestroyWindow(window);
	}

	window = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, flags);

	if (window == NULL)
	{
		LOG("Window could not be created! SDL_Error: %s\n", SDL_GetError());
	}
	else
	{
		//Get window surface
		screen_surface = SDL_GetWindowSurface(window);
	}
}






