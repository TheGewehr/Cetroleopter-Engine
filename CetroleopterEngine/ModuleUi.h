#ifndef _MODULE_UI_H_
#define _MODULE_UI_H_

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
	update_status PreUpdate(float dt) override;
	update_status PostUpdate(float dt) override;
	bool CleanUp();

	
private:

	bool InitializeImGui()const;
	
};

#endif