#ifndef _MODULEUI_H_
#define _MODULEUI_H_

#include "Module.h"
#include "Globals.h"
#include "imgui.h"
#include <vector>
#include "SDL/include/SDL.h"

class ModuleUi : public Module
{
public:
	ModuleUi(bool start_enabled = true);
	~ModuleUi();

	bool Init();
	update_status PreUpdate(float dt);
	update_status Update(float dt);
	update_status PostUpdate(float dt);
	bool CleanUp();

	
private:

	bool InitializeImGui()const;
	
};

#endif // !_MODULEUI_H_