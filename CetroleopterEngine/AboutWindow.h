#ifndef _ABOUT_WINDOW_H_
#define _ABOUT_WINDOW_H_

#include "ImGuiWindowBase.h"

//class ImGuiWindowBase;

class AboutWindow : public ImGuiWindowBase
{
public:
	AboutWindow(const char* name, bool isActive = false);
	~AboutWindow();

	bool Draw(ImGuiIO& io);
	bool CleanUp();

	//void UpdateFrameData(int frames, int ms);

private:
	
	bool AboutHeader();

};

#endif // !_ABOUT_WINDOW_H_

