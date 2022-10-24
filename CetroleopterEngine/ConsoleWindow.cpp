#include "ConsoleWindow.h"

#include "Application.h"


ConsoleWindow::ConsoleWindow(const char* name, bool isActive) : ImGuiWindowBase("Console", isActive = true)
{

}

ConsoleWindow::~ConsoleWindow()
{

}

bool ConsoleWindow::Draw(ImGuiIO& io)
{
	
	bool ret = true;


	ImGui::Begin(GetName(), nullptr, ImGuiWindowFlags_None);

	if (App->moduleUi->hoveringWindow == false)
		App->moduleUi->hoveringWindow = ImGui::IsWindowHovered(); // To know if the window is being moved

	for (uint i = 0; i < logs.size(); ++i)
	{
		ImGui::TextUnformatted(logs[i]);
	}

	ImGui::End();

	return ret;
	
}

bool ConsoleWindow::CleanUp()
{
	return true;
}

bool ConsoleWindow::AddLogsInConsole(const char* logStr)
{
	
	if (logs.size() + 1 > LIMIT_OF_LOGS)
	{
		ClearLogs();
	}

	char* tmp = _strdup(logStr);

	logs.push_back(tmp);

	return true;
}

void ConsoleWindow::ClearLogs()
{
	for (uint i = 0; i < logs.size(); ++i)
	{
		free(logs[i]);
	}
	
	logs.clear();
}