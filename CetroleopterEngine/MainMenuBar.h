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
	bool ViewMenuBar();
	bool HelpMenuBar();

private:
	bool wireframeMode = false;
	bool faceCullingMode = false;
	bool disableLights = false;
	bool showConsole = false;
	bool showConfig = true;
	//bool aboutON = false;
};

#endif 

