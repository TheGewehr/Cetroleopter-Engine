#ifndef _OJBECTS_INSPECTOR_WINDOW_H_
#define _OBJECTS_INSPECTOR_WINDOW_H_

#include "ImGuiWindowBase.h"
#include <vector>

class ModuleGameObject;

class ObjectsInspectorWindow : public ImGuiWindowBase
{
public:
	ObjectsInspectorWindow(const char* name, bool isActive = false);
	~ObjectsInspectorWindow();

	bool Draw(ImGuiIO& io);
	bool CleanUp();


private:
	
	bool InspectorWindowHeader();
	void HierarchyOptions();
	ModuleGameObject* InspectorObject = nullptr;

	enum HierarchyOptions
	{
		NONE = 0,
		SETPARENT,
		ADDCHILD,
		DELETEOBJECT		
	};


	int hierarchyDummy = 0;

	int buttonObjectID = 0;

};

#endif // !_OBJECTS_INSPECTOR_WINDOW_H_
