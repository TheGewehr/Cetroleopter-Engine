#ifndef _IMGUIWINDOW_H_
#define _IMGUIWINDOW_H_

#include "imgui.h"
#include "imconfig.h"
#include "imgui_internal.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl3.h"


class ImGuiWindow
{
public:


	ImGuiWindow(const char* name, bool isActive = true) : name(name), isActive(isActive)
	{}

	virtual ~ImGuiWindow()
	{}

	virtual bool Draw(ImGuiIO& io)
	{
		return true;
	}

	virtual bool CleanUp()
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

#endif // !_IMGUIWINDOW_H_