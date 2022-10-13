#include "Application.h"
#include "Globals.h"
#include "ModuleWindow.h"
#include "imgui.h"
#include "ModuleSceneIntro.h"
#include "AboutWindow.h"

#include "assimp/Include/version.h" // From assimp

AboutWindow::AboutWindow(const char* name, bool isActive) : ImGuiWindowBase("About", isActive = false)
{
	//fps = 0;
}

AboutWindow::~AboutWindow()
{
}

bool AboutWindow::Draw(ImGuiIO& io)
{
	bool ret = true;

	
	ImGui::Begin(GetName(), nullptr, ImGuiWindowFlags_None);

	if (App->moduleUi->hoveringWindow == false)
		App->moduleUi->hoveringWindow = ImGui::IsWindowHovered(); // To know if the window is being moved
	
	AboutHeader();
	
	ImGui::End();

	return ret;
}

bool AboutWindow::CleanUp()
{
	bool ret = true;

	return ret;
}

bool AboutWindow::AboutHeader()
{
	bool ret = true;
	/*Add an “About ..” modal window inside
			the “Help” menu that shows :
		○ Name of your Engine
			○ One(or few) line description
			○ Name of the Author with link to github page
			○ Libraries(with versions queried in real time)
			used with links to their web
			○ Full text of the license*/
	ImGui::Text("Cetreleopter Engine V0.5");
	ImGui::Spacing();

	ImGui::Bullet();
	if (ImGui::Button("Engine Repository"))
		ShellExecuteA(NULL, "open", "https://github.com/TheGewehr/Cetroleopter-Engine", NULL, NULL, SW_SHOWNORMAL);

	ImGui::Spacing();
	ImGui::Spacing();
	ImGui::Separator();
	ImGui::Spacing();
	ImGui::Spacing();


	ImGui::Text("Developers:");
	ImGui::Spacing();

	ImGui::BulletText("Alvaro Milla");
	ImGui::SameLine();
	if (ImGui::Button("mrmile"))
		ShellExecuteA(NULL, "open", "https://github.com/mrmile", NULL, NULL, SW_SHOWNORMAL);

	ImGui::BulletText("Alexandre Carreras");
	ImGui::SameLine();
	if (ImGui::Button("TheGewehr"))
		ShellExecuteA(NULL, "open", "https://github.com/TheGewehr", NULL, NULL, SW_SHOWNORMAL);
	ImGui::Spacing();

	ImGui::Spacing();
	ImGui::Spacing();
	ImGui::Separator();
	ImGui::Spacing();
	ImGui::Spacing();


	ImGui::Text("External libraries used:");
	ImGui::Spacing();
	SDL_version sdlVersion;
	SDL_GetVersion(&sdlVersion);
	ImGui::BulletText("SDL v%i.%i.%i", sdlVersion.major, sdlVersion.minor, sdlVersion.patch);
	ImGui::Spacing();
	ImGui::BulletText("Open GL v?"); //3.1 ?
	ImGui::Spacing();
	ImGui::BulletText("Glew v?"); // 2.1.0 ?
	ImGui::Spacing();
	ImGui::BulletText("ImGui v%s (Docking)", ImGui::GetVersion());
	ImGui::Spacing();
	ImGui::BulletText("Assimp v%i.%i.%i", aiGetVersionMajor(), aiGetVersionMinor(), aiGetVersionRevision());
	ImGui::Spacing();
	ImGui::BulletText("DevIL v1.8.0"); // 1.7.8 ?
	ImGui::Spacing();
	//Ray tracing library: https://github.com/engilas/raytracing-opengl ----- fork: https://github.com/lucciffer/raytracing-opengl
	ImGui::BulletText("MathGeoLib v?"); // 2.0 ?
	ImGui::Spacing();
	//ImGui::BulletText("PhysFS v3.0.2");
	//ImGui::Spacing();
	ImGui::BulletText("JSON Parser v?"); // 3.10.4 ?

	ImGui::Spacing();
	ImGui::Spacing();
	ImGui::Separator();
	ImGui::Spacing();
	ImGui::Spacing();


	//ImGui::TextColored(IMGUI_BLUE, "MIT License");
	ImGui::Text("MIT License");
	ImGui::Spacing();
	ImGui::Spacing();
	ImGui::Text("Copyright (c) 2022 - mrmile, TheGewehr");
	ImGui::Spacing();
	ImGui::Spacing();
	ImGui::TextWrapped("Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the \"Software\"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and /or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions: ");
	ImGui::Spacing();
	ImGui::Spacing();
	ImGui::TextWrapped("The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.");
	ImGui::Spacing();
	ImGui::Spacing();
	ImGui::TextWrapped("THE SOFTWARE IS PROVIDED \"AS IS\", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.");


	return ret;
}
