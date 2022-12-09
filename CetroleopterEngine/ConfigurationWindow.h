#ifndef _CONFIGURATIONWINDOW_H_
#define _CONFIGURATIONWINDOW_H_

#include "ImGuiWindowBase.h"
//#include "parson.h"

#define MAX_HISTOGRAM_SIZE 100

//class ImGuiWindowBase;

class ConfigurationWindow : public ImGuiWindowBase
{
public:
	ConfigurationWindow(const char* name, bool isActive = true);
	~ConfigurationWindow();

	bool Draw(ImGuiIO& io);
	bool CleanUp();

	//void UpdateFrameData(int frames, int ms);
	bool SaveRequest();
	bool LoadRequest();

	void UpdateFrameData(int frames, int ms);

	std::string Vendor;
	std::string GPU_Model;
	std::string Drivers;

private:
	
	bool WindowHeader();
	bool AnotherHeader();
	bool FPSHeader();
	bool HardwareHeader();

private:

	
	//Windows variables
	float brightness = 1.000f;
	int width;
	int height;
	bool checkFullscreen;
	bool checkResizable;
	bool checkBorderless;
	bool checkFullDesktop;
	bool checkVsync;

	// FPS Variable
	int fps;
	float fpsData[MAX_HISTOGRAM_SIZE];
	float msData[MAX_HISTOGRAM_SIZE];
};

#endif // !_CONFIGURATIONWINDOW_H_

