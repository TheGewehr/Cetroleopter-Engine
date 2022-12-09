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

	bool SaveRequest();
	bool LoadRequest();
private:

	bool FileMenuBar();
	bool EditMenuBar();
	bool CreateMenuBar();
	bool ViewMenuBar();
	bool HelpMenuBar();
	bool PlayPauseMenuBar();
	bool ExperimentalFeatures();

private:
	
	uint sceneTimer = 0;
	bool counterON = false;
};

#endif 

