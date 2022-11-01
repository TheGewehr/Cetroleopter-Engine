#ifndef _OJBECTS_INSPECTOR_WINDOW_H_
#define _OBJECTS_INSPECTOR_WINDOW_H_

#include "ImGuiWindowBase.h"
#include <vector>


class ObjectsInspectorWindow : public ImGuiWindowBase
{
public:
	ObjectsInspectorWindow(const char* name, bool isActive = false);
	~ObjectsInspectorWindow();

	bool Draw(ImGuiIO& io);
	bool CleanUp();


private:
	
	bool InspectorWindowHeader();

public:

	

};

#endif // !_OBJECTS_INSPECTOR_WINDOW_H_
