#ifndef _MODULEUI_H_
#define _MODULEUI_H_

#include "Module.h"
#include "Globals.h"
#include "imgui/imgui.h"
#include <vector>
#include "SDL/include/SDL.h"

class ImGuiWindow;
class ConfigurationWindow;

class ModuleUi : public Module
{
public:

	ModuleUi(bool start_enabled = true);
	~ModuleUi();

	bool Start();
	update_status PreUpdate(float dt);
	update_status Update(float dt);
	update_status PostUpdate(float dt);
	bool CleanUp();


	// list of ImGui Windows
	std::vector<ImGuiWindow*> list_ImGuiWindows;

	// list of windows ptrs
	ConfigurationWindow* configurationWindow = nullptr;

	bool hoveringWindow;

private:

	bool InitializeImGui()const;

	void AddImGuiWindow(ImGuiWindow* window);

	bool RenderImGuiWindows()const;

	bool GetEvent(SDL_Event* event);

	bool BeginRootWindow(ImGuiIO& io, const char* window_id, bool docking, ImGuiWindowFlags window_flags = ImGuiWindowFlags_None); // Generates a root window for docking.
	void BeginDockspace(ImGuiIO& io, const char* dockspace_id, ImGuiDockNodeFlags docking_flags = ImGuiDockNodeFlags_None, ImVec2 size = { 0.0f, 0.0f }); // Generates a new dockspace.

};

#endif // !_MODULEUI_H_