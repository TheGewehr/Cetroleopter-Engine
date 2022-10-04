#ifndef _IMGUIWINDOW_BASE_H_
#define _IMGUIWINDOW_BASE_H_

#include "imgui.h"
#include "imconfig.h"
#include "imgui_internal.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl3.h"


class ImGuiWindowBase
{
public:


	ImGuiWindowBase(const char* name, bool isActive = true) : name(name), isActive(isActive)
	{}

	virtual ~ImGuiWindowBase()
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

	void ChangeActive()
	{
		isActive = !isActive;
	}

	bool GetIsHover()const
	{
		return isHover;
	}

	bool GetIsClicked()const
	{
		return isClicked;
	}


public:

	const char* name;
	bool isActive;
	bool isHover;
	bool isClicked;
};

#endif // !_IMGUIWINDOW_BASE_H_