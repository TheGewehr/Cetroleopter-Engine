#ifndef _RESSOURCES_WINDOW_H_
#define _RESSOURCES_WINDOW_H_

#include "ImGuiWindowBase.h"

class RessourcesWindow : public ImGuiWindowBase
{
public:
	RessourcesWindow(const char* name, bool isActive = false);
	~RessourcesWindow();

	bool Draw(ImGuiIO& io);
	bool CleanUp();

	
private:

	void GenerateDockspace(ImGuiIO& io) const;										

	void DrawMenuBar() const;													 
	void DrawAssetsTree();															 
	void DrawFolderExplorer() const;													

	void DrawDirectoriesTree(const char* root_directory, const char* extension_to_filter);

private:

	char* directory_to_display;

};
#endif

