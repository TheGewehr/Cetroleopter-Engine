#include "Application.h"
#include "Globals.h"
#include "RessourcesWindow.h"
#include "imgui.h"
#include "IconsFontAwesome5.h"

#include <vector>
#include <algorithm>

#define MAX_DIRECTORY_SIZE 500

RessourcesWindow::RessourcesWindow(const char* name, bool isActive) : ImGuiWindowBase("Ressources", true)
{
	directory_to_display = new char[MAX_DIRECTORY_SIZE];

	sprintf_s(directory_to_display, MAX_DIRECTORY_SIZE, "%s", "Assets/");
}

RessourcesWindow::~RessourcesWindow()
{
}

bool RessourcesWindow::Draw(ImGuiIO& io)
{
	bool ret = true;

	DrawAssetsTree();
	DrawFolderExplorer();

	return ret;
}

bool RessourcesWindow::CleanUp()
{
	bool ret = true;

	return ret;
}

void RessourcesWindow::GenerateDockspace(ImGuiIO& io) const
{
	if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
	{
		ImGuiID dockspace_id = ImGui::GetID("Project##");
		ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_PassthruCentralNode);
	}
}


void RessourcesWindow::DrawAssetsTree()
{
	ImGui::Begin("AssetsTree", false);

	if (App->moduleUi->hoveringWindow == false)
		App->moduleUi->hoveringWindow = ImGui::IsWindowHovered();

	if (ImGui::TreeNodeEx("Assets/", ImGuiTreeNodeFlags_DefaultOpen))
	{
		DrawDirectoriesTree("Assets/", ".meta");
		ImGui::TreePop();
	}

	ImGui::End();
}

void RessourcesWindow::DrawFolderExplorer() const
{
	ImGui::Begin("FolderExplorer", false);

	
	if (App->moduleUi->hoveringWindow == false)
		App->moduleUi->hoveringWindow = ImGui::IsWindowHovered();

	
	for (uint i = 0; i < App->scene_intro->gameObjects.size(); i++)
	{
		ImGui::PushID(i);
		
		if (ImGui::Button(ICON_FA_FILE))
		{
			for (uint j = 0; j < App->scene_intro->gameObjects.size(); j++)
			{
				if (App->scene_intro->gameObjects[j]->isObjectSelected_ == true && App->scene_intro->gameObjects[i]->isObjectSelected_ == false)
				{
					App->scene_intro->gameObjects[j]->isObjectSelected_ = false;
				}
			}
			
			App->scene_intro->gameObjects[i]->SelectObject();
		}

		ImGui::SameLine();
		ImGui::Text(App->scene_intro->gameObjects[i]->GetName().c_str());

		ImGui::PopID();

		
	}

	ImGui::End();
}

void RessourcesWindow::DrawDirectoriesTree(const char* root_directory, const char* extension_to_filter)
{
	std::vector<std::string> directories;
	std::vector<std::string> files;

	std::string root_dir = root_directory;

	App->moduleFS->DiscoverFiles(root_dir.c_str(), files, directories);
	
	for (uint i = 0; i < directories.size(); ++i)
	{
		std::string path = root_dir + directories[i] + ("/");

		if (ImGui::TreeNodeEx(path.c_str(), 0, "%s/", directories[i].c_str()))
		{
			DrawDirectoriesTree(path.c_str(), extension_to_filter);
			path.clear();
			ImGui::TreePop();
		}
	}

	std::sort(files.begin(), files.end());

	for (uint i = 0; i < files.size(); ++i)
	{
		if (ImGui::TreeNodeEx(files[i].c_str(), ImGuiTreeNodeFlags_Leaf))
		{
			if (ImGui::IsItemClicked())
			{
				sprintf_s(directory_to_display, MAX_DIRECTORY_SIZE, "%s%s", root_dir.c_str(), files[i].c_str());
			}

			ImGui::TreePop();
		}
	}

	directories.clear();
	files.clear();
	root_dir.clear();
}
