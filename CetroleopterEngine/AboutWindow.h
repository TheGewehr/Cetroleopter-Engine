#ifndef _ABOUT_WINDOW_H_
#define _ABOUT_WINDOW_H_

#include "ImGuiWindowBase.h"

#define MAX_HISTOGRAM_SIZE 100

//class ImGuiWindowBase;

class AboutWindow : public ImGuiWindowBase
{
public:
	AboutWindow(const char* name, bool isActive = true);
	~AboutWindow();

	bool Draw(ImGuiIO& io);
	bool CleanUp();

	//void UpdateFrameData(int frames, int ms);

private:
	
	bool AboutHeader();

private:


};

#endif // !_ABOUT_WINDOW_H_

