#ifndef _MODULEUI_H_
#define _MODULEUI_H_

#include "Module.h"
#include "Globals.h"
#include "imgui/imgui.h"
#include <vector>
#include "SDL/include/SDL.h"

#include "ImGuiWindowBase.h"

class ImGuiWindowBase;
class ConfigurationWindow;
class MainMenuBar;
class AboutWindow;
class ConsoleWindow;
class GameObjectsWindow;
class ObjectsInspectorWindow;
class RessourcesWindow;

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

	// For the console window
	void AddLogFromModuleUi(const char* str);

	void UpdateFrameData(float frames, float ms);
	

	// list of ImGui Windows
	std::vector<ImGuiWindowBase*> list_ImGuiWindows;

	// list of windows ptrs
	ConfigurationWindow* configurationWindow = nullptr;
	MainMenuBar* mainMenuBar = nullptr;
	AboutWindow* aboutWindow = nullptr;
	ConsoleWindow* consoleWindow = nullptr;
	GameObjectsWindow* gameObjectsWindow = nullptr;
	ObjectsInspectorWindow* objectsInspectorWindow = nullptr;
	RessourcesWindow* ressourcesWindow = nullptr;

	bool hoveringWindow;

	int currentSelectedObject = -1;

private:

	bool InitializeImGui()const;

	void AddImGuiWindow(ImGuiWindowBase* window);

	bool RenderImGuiWindows()const;

	bool GetEvent(SDL_Event* event);

	bool BeginRootWindow(ImGuiIO& io, const char* window_id, bool docking, ImGuiWindowFlags window_flags = ImGuiWindowFlags_None); // Generates a root window for docking.
	void BeginDockspace(ImGuiIO& io, const char* dockspace_id, ImGuiDockNodeFlags docking_flags = ImGuiDockNodeFlags_None, ImVec2 size = { 0.0f, 0.0f }); // Generates a new dockspace.

	
};

#endif // !_MODULEUI_H_