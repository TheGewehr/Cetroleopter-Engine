#ifndef _GAMEOJBECTS_WINDOW_H_
#define _GAMEOBJECTS_WINDOW_H_

#include "ImGuiWindowBase.h"
#include <vector>
#include <string>

class ModuleGameObject;

class GameObjectsWindow : public ImGuiWindowBase
{
public:
	GameObjectsWindow(const char* name, bool isActive = false);
	~GameObjectsWindow();

	bool Draw(ImGuiIO& io);
	bool CleanUp();


private:
	
	bool ObjectWindowHeader();

	const char* GetObjectName(std::string name)const;

	void TreeProcessing(std::vector<ModuleGameObject*> objects);

public:
	

};

#endif // !_GAMEOBJECTS_WINDOW_H_
