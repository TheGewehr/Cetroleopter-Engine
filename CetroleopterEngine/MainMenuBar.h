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
	//bool wireframeMode = false; Already inside module renderer
	//bool faceCullingMode = false; Already inside module renderer
	bool disableLights = false;
	bool showConsole = false;
	bool showSettings = true;
	bool aboutON = false;
};

#endif 

