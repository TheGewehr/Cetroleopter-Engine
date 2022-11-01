#ifndef _GAMEOJBECTS_WINDOW_H_
#define _GAMEOBJECTS_WINDOW_H_

#include "ImGuiWindowBase.h"
#include <vector>


class GameObjectsWindow : public ImGuiWindowBase
{
public:
	GameObjectsWindow(const char* name, bool isActive = false);
	~GameObjectsWindow();

	bool Draw(ImGuiIO& io);
	bool CleanUp();


private:
	
	bool ObjectWindowHeader();
	bool ObjectWindowButton(int obj_id);

public:


};

#endif // !_GAMEOBJECTS_WINDOW_H_
