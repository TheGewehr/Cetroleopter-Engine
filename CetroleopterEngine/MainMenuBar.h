#ifndef _MAINMENUBAR_H_
#define _MAINMENUBAR_H_

#include "ImGuiWindowBase.h"

//class ImGuiWindowBase;

class MainMenuBar: public ImGuiWindowBase
{
public:
	MainMenuBar(const char* name, bool isActive = false);
	~MainMenuBar();

	bool Draw(ImGuiIO& io);
	bool CleanUp();

private:

	bool CreateMainMenuBar();

	//bool aboutON = false;
};

#endif 

