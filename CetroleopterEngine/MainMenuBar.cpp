#include "Application.h"
#include "Globals.h"
#include "ModuleWindow.h"
#include "imgui.h"
#include "IconsFontAwesome5.h"

#include "ModuleSceneIntro.h"
#include "ModuleCamera3D.h"
#include "ModuleInput.h"

#include "MainMenuBar.h"
#include "AboutWindow.h"
#include "ConfigurationWindow.h"
#include "ModuleModelImport.h"
#include "ModuleSaveLoad.h"
#include "ConsoleWindow.h"
#include "ModuleSceneIntro.h"

#include "ModuleAudio.h"
#include "ModuleAudioSourceComponent.h"
#include "Game/Library/Sounds/Wwise_IDs.h"


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
	ExperimentalFeatures();

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

		if (ImGui::MenuItem(ICON_FA_SAVE " Save Configuration"))
		{
			App->save_load->saveConfigurationTrigger = true;
		}
		if (ImGui::MenuItem(ICON_FA_FILE_UPLOAD " Load Configuration"))
		{
			App->save_load->loadConfigurationTrigger = true;
		}
		ImGui::Separator();
		if (App->input->singleTextureLoaded == true)
		{
			ImGui::Text(ICON_FA_EXCLAMATION_TRIANGLE " Cannot Save or load Scene.\nYou have loaded an alone \ntexture as game object.");
		}
		else if (App->input->singleTextureLoaded == false)
		{
			if (ImGui::MenuItem(ICON_FA_SAVE " Save Scene"))
			{
				App->save_load->saveSceneTrigger = true;
			}
			if (ImGui::MenuItem(ICON_FA_FILE_UPLOAD " Load Scene"))
			{
				App->save_load->loadSceneTrigger = true;

			}
		}
		ImGui::Separator();
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
			App->modelImport->LoadModel_Textured(App->scene_intro->CreateEmptyGameObject(nullptr, "Cube"), "Assets/Primitives/cube_primitive.fbx", "Assets/WhiteTexture.png");
		}
		if (ImGui::MenuItem("Sphere"))
		{
			App->modelImport->LoadModel_Textured(App->scene_intro->CreateEmptyGameObject(nullptr, "Sphere"), "Assets/Primitives/sphere_primitive.fbx", "Assets/WhiteTexture.png");
		}
		if (ImGui::MenuItem("Cone"))
		{
			App->modelImport->LoadModel_Textured(App->scene_intro->CreateEmptyGameObject(nullptr, "Cone"), "Assets/Primitives/cone_primitive.fbx", "Assets/WhiteTexture.png");
		}
		if (ImGui::MenuItem("Pyramid"))
		{
			App->modelImport->LoadModel_Textured(App->scene_intro->CreateEmptyGameObject(nullptr, "Pyramid"), "Assets/Primitives/pyramid_primitive.fbx", "Assets/WhiteTexture.png");
		}
		if (ImGui::MenuItem("Cylinder"))
		{
			App->modelImport->LoadModel_Textured(App->scene_intro->CreateEmptyGameObject(nullptr, "Cylinder"), "Assets/Primitives/cylinder_primitive.fbx", "Assets/WhiteTexture.png");
		}
		if (ImGui::MenuItem("Torus"))
		{
			App->modelImport->LoadModel_Textured(App->scene_intro->CreateEmptyGameObject(nullptr, "Torus"), "Assets/Primitives/torus_primitive.fbx", "Assets/WhiteTexture.png");
		}
		if (ImGui::MenuItem("Polyhedron Ball"))
		{
			App->modelImport->LoadModel_Textured(App->scene_intro->CreateEmptyGameObject(nullptr, "Polyhedron"), "Assets/Primitives/polyhedron_primitive.fbx", "Assets/WhiteTexture.png");
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
			for (int i = 0; i < App->scene_intro->gameObjects.size(); i++)
			{
				if (App->scene_intro->gameObjects[i]->GetName() == "Train6")
				{
					if (App->scene_intro->sceneTimer > 0)
					{
						App->scene_intro->gameObjects[i]->GetAudioSourceComponent()->sound->PlayEvent_ID(AK::EVENTS::TRAINRESUME);
						App->scene_intro->trainTimer.Resume();
					}
					else if (App->scene_intro->sceneTimer == 0)
					{
						App->scene_intro->gameObjects[i]->GetAudioSourceComponent()->sound->PlayEvent_ID(AK::EVENTS::TRAINPLAY);
						App->scene_intro->trainTimer.Start();
					}
				}
			}

			counterON = true;
		}

		if (ImGui::MenuItem(ICON_FA_STOP " Stop"))
		{
			counterON = false;

			for (int i = 0; i < App->scene_intro->gameObjects.size(); i++)
			{
				if (App->scene_intro->gameObjects[i]->GetName() == "Train6")
				{
					App->scene_intro->gameObjects[i]->GetAudioSourceComponent()->sound->PlayEvent_ID(AK::EVENTS::TRAINPAUSE);
					App->scene_intro->trainTimer.Pause();
				}
			}
		}

		if (ImGui::MenuItem(ICON_FA_BACKWARD " Reset"))
		{
			App->scene_intro->sceneTimer = 0;
			App->scene_intro->trainTimer.Reset();

			for (int i = 0; i < App->scene_intro->gameObjects.size(); i++)
			{
				if (App->scene_intro->gameObjects[i]->GetName() == "Train6")
				{
					App->scene_intro->gameObjects[i]->GetAudioSourceComponent()->sound->PlayEvent_ID(AK::EVENTS::TRAINSTOP);
					App->scene_intro->trainTimer.Reset();
					if (counterON == true)
					{
						App->scene_intro->gameObjects[i]->GetAudioSourceComponent()->sound->PlayEvent_ID(AK::EVENTS::TRAINPLAY);
						App->scene_intro->trainTimer.Start();
					}
				}
			}
		}

		ImGui::Separator();

		ImGui::Text("\n Game time: %i \n", App->scene_intro->sceneTimer);

		//if (counterON == true)
		//{
		//	App->scene_intro->sceneTimer++;
		//	App->scene_intro->trainTimer++;
		//}

		ImGui::Separator();

		if (ImGui::MenuItem(ICON_FA_PLAY " Play BG music"))
		{
			for (int i = 0; i < App->scene_intro->gameObjects.size(); i++)
			{
				if (App->scene_intro->gameObjects[i]->GetName() == "RandomComputer5")
				{
					if(wasMusicPaused == false) App->scene_intro->gameObjects[i]->GetAudioSourceComponent()->sound->PlayEvent_ID(AK::EVENTS::MUSICLOOPPLAY);
					else if (wasMusicPaused == true) App->scene_intro->gameObjects[i]->GetAudioSourceComponent()->sound->PlayEvent_ID(AK::EVENTS::MUSICLOOPRESUME);
				}
			}
			wasMusicPaused = false;
		}

		if (ImGui::MenuItem(ICON_FA_STOP " Stop BG music"))
		{
			wasMusicPaused = true;
			for (int i = 0; i < App->scene_intro->gameObjects.size(); i++)
			{
				if (App->scene_intro->gameObjects[i]->GetName() == "RandomComputer5")
				{
					App->scene_intro->gameObjects[i]->GetAudioSourceComponent()->sound->PlayEvent_ID(AK::EVENTS::MUSICLOOPPAUSE);
				}
			}
		}

		if (ImGui::MenuItem(ICON_FA_BACKWARD " Reset BG music"))
		{
			for (int i = 0; i < App->scene_intro->gameObjects.size(); i++)
			{
				if (App->scene_intro->gameObjects[i]->GetName() == "RandomComputer5")
				{
					if (wasMusicPaused == false)
					{
						App->scene_intro->gameObjects[i]->GetAudioSourceComponent()->sound->PlayEvent_ID(AK::EVENTS::MUSICLOOPSTOP);
						App->scene_intro->gameObjects[i]->GetAudioSourceComponent()->sound->PlayEvent_ID(AK::EVENTS::MUSICLOOPPLAY);
					}
					else if(wasMusicPaused == true) App->scene_intro->gameObjects[i]->GetAudioSourceComponent()->sound->PlayEvent_ID(AK::EVENTS::MUSICLOOPSTOP);
				}
			}
		}

		ImGui::EndMenu();
	}

	return ret;
}

bool MainMenuBar::ExperimentalFeatures()
{
	bool ret = true;

	if (ImGui::BeginMenu("Experimental features toggling"))
	{
		ImGui::Text(ICON_FA_EXCLAMATION_TRIANGLE " WARNING!");
		ImGui::Text("Features in this section \nin spite of being fully implemented, \nthey are quite buggy and may cause \nunnexpected results.\n");
		ImGui::Separator();

		if (ImGui::Checkbox("Enable Mouse Picking", &App->camera->mousePickExpFeatureActivated))
		{

		}

		if (ImGui::Checkbox("Enable Mesh Transformations", &App->camera->transformExpFeatureActivated))
		{

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