﻿#include "Application.h"
#include "Globals.h"
#include "ModuleWindow.h"
#include "imgui.h"
#include "IconsFontAwesome5.h"

#include "ModuleSceneIntro.h"
#include "MainMenuBar.h"
#include "AboutWindow.h"
#include "ConfigurationWindow.h"
#include "ModuleModelImport.h"
#include "ModuleSaveLoad.h"
#include "ConsoleWindow.h"

MainMenuBar::MainMenuBar(const char* name, bool isActive) : ImGuiWindowBase("MainMenuBar", isActive = true)
{
	
}

MainMenuBar::~MainMenuBar()
{
}

bool MainMenuBar::Draw(ImGuiIO& io)
{
	bool ret = true;
	

	//ImGui::Begin(GetName(), nullptr, ImGuiWindowFlags_None);
	ImGui::BeginMainMenuBar();

	if (App->moduleUi->hoveringWindow == false)
		App->moduleUi->hoveringWindow = ImGui::IsWindowHovered(); // To know if the window is being moved

	FileMenuBar();
	EditMenuBar();
	CreateMenuBar();
	ViewMenuBar();
	HelpMenuBar();
	PlayPauseMenuBar();

	//ImGui::End();
	ImGui::EndMainMenuBar();

	return ret;
}

bool MainMenuBar::CleanUp()
{
	bool ret = true;

	return ret;
}

bool MainMenuBar::FileMenuBar()
{
	bool ret = true;

	if (ImGui::BeginMenu("File"))
	{

		if (ImGui::MenuItem(" Save Configuration"))
		{
			App->save_load->saveConfigurationTrigger = true;
		}
		if (ImGui::MenuItem(" Load Configuration"))
		{
			App->save_load->loadConfigurationTrigger = true;
		}
		if (ImGui::MenuItem(ICON_FA_SAVE " Save Scene"))
		{
			App->save_load->saveSceneTrigger = true;
		}
		if (ImGui::MenuItem(ICON_FA_FILE_UPLOAD " Load Scene"))
		{
			App->save_load->loadSceneTrigger = true;
		}
		if (ImGui::MenuItem(ICON_FA_DOOR_OPEN " Exit"))
		{
			App->appExit = true;
		}

		ImGui::EndMenu();
	}

	return ret;
}

bool MainMenuBar::EditMenuBar()
{
	bool ret = true;

	if (ImGui::BeginMenu("Edit"))
	{
		if (ImGui::MenuItem(ICON_FA_CUT " Cut"))
		{

		}
		if (ImGui::MenuItem(ICON_FA_COPY " Copy"))
		{

		}
		if (ImGui::MenuItem(ICON_FA_PASTE " Paste"))
		{

		}
		ImGui::Separator();
		if (ImGui::MenuItem(ICON_FA_CIRCLE_NOTCH " Settings", "", App->moduleUi->configurationWindow->isActive))
		{
			App->moduleUi->configurationWindow->ChangeActive();
		}
		if (ImGui::MenuItem(ICON_FA_WINDOW_RESTORE " Console", "", App->moduleUi->consoleWindow->isActive))
		{
			App->moduleUi->consoleWindow->ChangeActive();
		}
		ImGui::Separator();
		if (ImGui::MenuItem("Load Test Model - BakerHouse"))
		{
			App->modelImport->LoadModel_Textured(App->scene_intro->CreateEmptyGameObject(nullptr, "BakerHouse"), "Assets/BakerHouse_BIG.fbx", "Assets/bakeHouse.png");
		}
		if (ImGui::MenuItem("Load Test Model - BusStation"))
		{
			App->modelImport->LoadModel_Textured(App->scene_intro->CreateEmptyGameObject(nullptr, "BusStation"), "Assets/BusStation.fbx", "Assets/lambert23_Base_Color.png");
		}
		if (ImGui::MenuItem("Load Test Model - Zotac RTX_GPU"))
		{
			App->modelImport->LoadModel_Textured(App->scene_intro->CreateEmptyGameObject(nullptr, "GraphicCard"), "Assets/graphic_card.fbx", "Assets/graphic_card_Base_Color.png");
		}

		ImGui::EndMenu();
	}

	return ret;
}

bool MainMenuBar::CreateMenuBar()
{
	bool ret = true;

	if (ImGui::BeginMenu("Create"))
	{
		if (ImGui::MenuItem("Cube"))
		{
			App->modelImport->LoadModel_Textured(App->scene_intro->CreateEmptyGameObject(nullptr, "Cube"), "Assets/Primitives/cube_primitive.fbx", nullptr);
		}
		if (ImGui::MenuItem("Sphere"))
		{
			App->modelImport->LoadModel_Textured(App->scene_intro->CreateEmptyGameObject(nullptr, "Sphere"), "Assets/Primitives/sphere_primitive.fbx", nullptr);
		}
		if (ImGui::MenuItem("Cone"))
		{
			App->modelImport->LoadModel_Textured(App->scene_intro->CreateEmptyGameObject(nullptr, "Cone"), "Assets/Primitives/cone_primitive.fbx", nullptr);
		}
		if (ImGui::MenuItem("Pyramid"))
		{
			App->modelImport->LoadModel_Textured(App->scene_intro->CreateEmptyGameObject(nullptr, "Pyramid"), "Assets/Primitives/pyramid_primitive.fbx", nullptr);
		}
		if (ImGui::MenuItem("Cylinder"))
		{
			App->modelImport->LoadModel_Textured(App->scene_intro->CreateEmptyGameObject(nullptr, "Cylinder"), "Assets/Primitives/cylinder_primitive.fbx", nullptr);
		}
		if (ImGui::MenuItem("Torus"))
		{
			App->modelImport->LoadModel_Textured(App->scene_intro->CreateEmptyGameObject(nullptr, "Torus"), "Assets/Primitives/torus_primitive.fbx", nullptr);
		}
		if (ImGui::MenuItem("Polyhedron Ball"))
		{
			App->modelImport->LoadModel_Textured(App->scene_intro->CreateEmptyGameObject(nullptr, "Polyhedron"), "Assets/Primitives/polyhedron_primitive.fbx", nullptr);
		}

		ImGui::EndMenu();
	}

	return ret;
}

bool MainMenuBar::ViewMenuBar()
{
	bool ret = true;

	if (ImGui::BeginMenu("View"))
	{
		
		if (ImGui::Checkbox("Wireframe Mode", &App->renderer3D->wireframeMode))
		{
			//App->renderer3D->wireframeMode = !App->renderer3D->wireframeMode; Not needed (the change of state is done up on the if statement if (ImGui::Checkbox("Wireframe Mode", &App->renderer3D->wireframeMode))
		}
		if (ImGui::Checkbox("Disable Textures", &App->renderer3D->texturesOFF))
		{
			
		}
		if (ImGui::Checkbox("Cull Faces", &App->renderer3D->faceCullingMode))
		{

		}
		if (ImGui::Checkbox("Disable Lights", &App->renderer3D->disableLights))
		{

		}
		if (ImGui::Checkbox("Disable AO (Ambient Occlusion)", &App->renderer3D->disableAO))
		{

		}
		//if (ImGui::Checkbox("Show Windows Console", &App->renderer3D->showConsole))
		//{
		//
		//}

		ImGui::EndMenu();
	}

	return ret;
}

bool MainMenuBar::HelpMenuBar()
{
	bool ret = true;
	
	if (ImGui::BeginMenu("Help"))
	{
		if (ImGui::MenuItem(ICON_FA_INFO_CIRCLE " Go to: https://github.com/TheGewehr/Cetroleopter-Engine"))
		{
			App->OpenBrowserWebPage("https://github.com/TheGewehr/Cetroleopter-Engine");
		}

		if (ImGui::MenuItem(ICON_FA_INFO_CIRCLE " About", "", App->moduleUi->aboutWindow->isActive))
		{
			App->moduleUi->aboutWindow->ChangeActive();

		}

		ImGui::EndMenu();
	}

	return ret;
}

bool MainMenuBar::PlayPauseMenuBar()
{
	bool ret = true;

	if (ImGui::BeginMenu("Play/Stop", true))
	{
		if (ImGui::MenuItem(ICON_FA_PLAY " Play"))
		{
			counterON = true;
		}

		if (ImGui::MenuItem(ICON_FA_STOP " Stop"))
		{
			counterON = false;
		}

		if (ImGui::MenuItem(ICON_FA_BACKWARD " Reset"))
		{
			sceneTimer = 0;
		}

		ImGui::Separator();

		ImGui::Text("\n Game time: %i \n", sceneTimer);

		if (counterON == true)
		{
			sceneTimer++;
		}

		ImGui::EndMenu();
	}

	return ret;
}

bool MainMenuBar::SaveRequest()
{
	// view menu 
	json_object_dotset_boolean(json_object(App->save_load->configurationFile), "MenuBar.View.WireframeMode", App->renderer3D->wireframeMode);
	json_object_dotset_boolean(json_object(App->save_load->configurationFile), "MenuBar.View.DisableTextures", App->renderer3D->texturesOFF);
	json_object_dotset_boolean(json_object(App->save_load->configurationFile), "MenuBar.View.FaceCullingMode", App->renderer3D->faceCullingMode);
	json_object_dotset_boolean(json_object(App->save_load->configurationFile), "MenuBar.View.DisableLights", App->renderer3D->disableLights);
	json_object_dotset_boolean(json_object(App->save_load->configurationFile), "MenuBar.View.DisableAO", App->renderer3D->disableAO);
	//json_object_dotset_boolean(json_object(App->save_load->configurationFile), "MenuBar.View.ShowConsole", App->renderer3D->showConsole);

	// edit menu
	json_object_dotset_boolean(json_object(App->save_load->configurationFile), "MenuBar.Edit.SettingsWindow", App->moduleUi->configurationWindow->isActive);
	json_object_dotset_boolean(json_object(App->save_load->configurationFile), "MenuBar.Edit.ConsoleWindow", App->moduleUi->consoleWindow->isActive);

	return true;
}

bool MainMenuBar::LoadRequest()
{
	// load view tab parameters
	App->renderer3D->wireframeMode = (bool)json_object_dotget_boolean(json_object(App->save_load->configurationFile), "MenuBar.View.WireframeMode");
	App->renderer3D->texturesOFF = (bool)json_object_dotget_boolean(json_object(App->save_load->configurationFile), "MenuBar.View.DisableTextures");
	App->renderer3D->faceCullingMode = (bool)json_object_dotget_boolean(json_object(App->save_load->configurationFile), "MenuBar.View.FaceCullingMode");
	App->renderer3D->disableLights = (bool)json_object_dotget_boolean(json_object(App->save_load->configurationFile), "MenuBar.View.DisableLights");
	App->renderer3D->disableAO = (bool)json_object_dotget_boolean(json_object(App->save_load->configurationFile), "MenuBar.View.DisableAO");
	//App->renderer3D->showConsole = (bool)json_object_dotget_boolean(json_object(App->save_load->configurationFile), "MenuBar.View.ShowConsole");
	
	// load edit tab parameters
	App->moduleUi->configurationWindow->isActive = (bool)json_object_dotget_boolean(json_object(App->save_load->configurationFile), "MenuBar.Edit.SettingsWindow");
	App->moduleUi->consoleWindow->isActive = (bool)json_object_dotget_boolean(json_object(App->save_load->configurationFile), "MenuBar.Edit.ConsoleWindow");

	return true;
}