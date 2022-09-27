#ifndef _IMGUIWINDOW_MANAGER_H_
#define _IMGUIWINDOW_MANAGER_H_

#include "imgui.h"
#include "imconfig.h"
#include "imgui_internal.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl3.h"


class ImGuiWindowManager
{
public:


	ImGuiWindowManager(const char* name, bool isActive = true) : name(name), isActive(isActive)
	{}

	virtual ~ImGuiWindowManager()
	{}

	virtual bool Draw(ImGuiIO& io)
	{
		return true;
	}

	void Enable()
	{
		if (!isActive)
			isActive = true;
	}

	void Disable()
	{
		if (isActive)
			isActive = false;
	}

	virtual bool CleanUp()
	{
		return true;
	}

	const char* GetName()const
	{
		return name;
	}

	bool GetIsActive()const
	{
		return isActive;
	}

	bool GetIsHover()const
	{
		return isHover;
	}

	bool GetIsClicked()const
	{
		return isClicked;
	}


private:

	const char* name;
	bool isActive;
	bool isHover;
	bool isClicked;
};

#endif // !_IMGUIWINDOW_MANAGER_H_