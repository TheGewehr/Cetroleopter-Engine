#ifndef _CONSOLE_WINDOW_H_
#define _CONSOLE_WINDOW_H_

#include "ImGuiWindowBase.h"
#include <vector>

#define LIMIT_OF_LOGS 10000

class ConsoleWindow : public ImGuiWindowBase
{
public:
	ConsoleWindow(const char* name, bool isActive = false);
	~ConsoleWindow();

	bool Draw(ImGuiIO& io);
	bool CleanUp();

	bool AddLogsInConsole(const char* logStr);

private:
	
	void ClearLogs();

public:

	std::vector<char*> logs;

};

#endif // !_CONSOLE_WINDOW_H_
