#include "Application.h"
#include "Globals.h"
#include "ModuleWindow.h"
#include "imgui.h"
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

		if (ImGui::MenuItem("Save Project"))
		{
			App->save_load->saveConfigurationTrigger = true;
		}
		if (ImGui::MenuItem("Load Project"))
		{
			App->save_load->loadConfigurationTrigger = true;
		}
		if (ImGui::MenuItem("Exit"))
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
		if (ImGui::MenuItem("Cut"))
		{

		}
		if (ImGui::MenuItem("Copy"))
		{

		}
		if (ImGui::MenuItem("Paste"))
		{

		}
		ImGui::Separator();
		if (ImGui::MenuItem("Settings", "", App->moduleUi->configurationWindow->isActive))
		{
			App->moduleUi->configurationWindow->ChangeActive();
		}
		if (ImGui::MenuItem("Console", "", App->moduleUi->consoleWindow->isActive))
		{
			App->moduleUi->consoleWindow->ChangeActive();
		}
		ImGui::Separator();
		if (ImGui::MenuItem("Load Test Model - BakerHouse"))
		{
			App->modelImport->LoadModel_Textured("Assets/BakerHouse_BIG.fbx", "Assets/bakeHouse.png");
		}
		if (ImGui::MenuItem("Load Test Model - BusStation"))
		{
			App->modelImport->LoadModel_Textured("Assets/BusStation.fbx", "Assets/lambert23_Base_Color.png");
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
			App->modelImport->LoadMesh("Assets/Primitives/cube_primitive.fbx");
		}
		if (ImGui::MenuItem("Sphere"))
		{
			App->modelImport->LoadMesh("Assets/Primitives/sphere_primitive.fbx");
		}
		if (ImGui::MenuItem("Cone"))
		{
			App->modelImport->LoadMesh("Assets/Primitives/cone_primitive.fbx");
		}
		if (ImGui::MenuItem("Pyramid"))
		{
			App->modelImport->LoadMesh("Assets/Primitives/pyramid_primitive.fbx");
		}
		if (ImGui::MenuItem("Cylinder"))
		{
			App->modelImport->LoadMesh("Assets/Primitives/cylinder_primitive.fbx");
		}
		if (ImGui::MenuItem("Torus"))
		{
			App->modelImport->LoadMesh("Assets/Primitives/torus_primitive.fbx");
		}
		if (ImGui::MenuItem("Polyhedron Ball"))
		{
			App->modelImport->LoadMesh("Assets/Primitives/polyhedron_primitive.fbx");
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
	
	if (ImGui::BeginMenu("Help",true))
	{
		if (ImGui::MenuItem("Go to: https://github.com/TheGewehr/Cetroleopter-Engine"))
		{
			App->OpenBrowserWebPage("https://github.com/TheGewehr/Cetroleopter-Engine");
		}

		if (ImGui::MenuItem("About", "", App->moduleUi->aboutWindow->isActive))
		{
			App->moduleUi->aboutWindow->ChangeActive();

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