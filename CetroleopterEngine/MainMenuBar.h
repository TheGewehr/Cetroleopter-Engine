#ifndef _MAINMENUBAR_H_
#define _MAINMENUBAR_H_

#include "ImGuiWindowBase.h"

//class ImGuiWindowBase;

class MainMenuBar: public ImGuiWindowBase
{
public:
	MainMenuBar(const char* name, bool isActive = true);
	~MainMenuBar();

	bool Draw(ImGuiIO& io);
	bool CleanUp();

private:

	bool FileMenuBar();
	bool EditMenuBar();
	bool CreateMenuBar();
	bool ViewMenuBar();
	bool HelpMenuBar();

private:
	
};

#endif 

