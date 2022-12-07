#ifndef _DEBUG_SCENE_VIEW_WINDOW_H_
#define _DEBUG_SCENE_VIEW_WINDOW_H_

#include "ImGuiWindowBase.h"


class DebugSceneViewWindow : public ImGuiWindowBase
{
public:
	
	DebugSceneViewWindow(const char* name, bool isActive = false);
	~DebugSceneViewWindow();

	bool Draw(ImGuiIO& io);
	bool CleanUp();

	//void UpdateFrameData(int frames, int ms);

private:

	bool DrawScene();

private:

	ImVec2					tex_size;
	ImVec2					tex_origin;
	ImVec2					cursor_pos;

};

#endif // !_DEBUG_SCENE_VIEW_WINDOW_H_

