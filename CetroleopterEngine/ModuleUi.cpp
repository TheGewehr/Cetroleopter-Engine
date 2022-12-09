#include "glew/include/GL/glew.h"

#include "SDL/include/SDL_opengl.h"
#include <gl/GL.h>
#include <gl/GLU.h>

#include "Globals.h"

#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_impl_sdl.h"
#include "IconsFontAwesome5.h"


#include "ModuleUi.h"
#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRenderer3D.h"
//#include "OpenGL.h"

#include "ImGuiWindowBase.h"
#include "ConfigurationWindow.h"
#include "MainMenuBar.h"
#include "AboutWindow.h"
#include "ConsoleWindow.h"
#include "GameObjectsWindow.h"
#include "ObjectsInspectorWindow.h"
#include "RessourcesWindow.h"

ModuleUi::ModuleUi(bool start_enabled) : Module(start_enabled),
configurationWindow(new ConfigurationWindow("ConfigurationWindow", true)),
mainMenuBar(new MainMenuBar("MainMenuBar", true)),
aboutWindow(new AboutWindow("AboutWindow", false)),
consoleWindow(new ConsoleWindow("ConsoleWindow", true)),
gameObjectsWindow(new GameObjectsWindow("GameObjectsWindow", true)),
objectsInspectorWindow(new ObjectsInspectorWindow("ObjectsInspectorWindow", true)),
ressourcesWindow(new RessourcesWindow("Ressources", true))
{
   AddImGuiWindow(configurationWindow);
   AddImGuiWindow(mainMenuBar);
   AddImGuiWindow(aboutWindow);
   AddImGuiWindow(consoleWindow);
   AddImGuiWindow(gameObjectsWindow);
   AddImGuiWindow(objectsInspectorWindow);
   AddImGuiWindow(ressourcesWindow);

}

ModuleUi::~ModuleUi()
{
   std::vector<ImGuiWindowBase*>::reverse_iterator item = list_ImGuiWindows.rbegin();
   while (item != list_ImGuiWindows.rend())
   {
       (*item)->CleanUp();
       delete *item;
       ++item;
   }
}

bool ModuleUi::Start()
{
    InitializeImGui();

    App->moduleUi->configurationWindow->Vendor = (const char*)glGetString(GL_VENDOR);
    App->moduleUi->configurationWindow->GPU_Model = (const char*)glGetString(GL_RENDERER);
    App->moduleUi->configurationWindow->Drivers = (const char*)glGetString(GL_VERSION);

    ImGuiIO& io = ImGui::GetIO();
    io.Fonts->AddFontDefault();

    // merge in icons from Font Awesome
    static const ImWchar icons_ranges[] = { ICON_MIN_FA, ICON_MAX_16_FA, 0 };
    ImFontConfig icons_config; icons_config.MergeMode = true; icons_config.PixelSnapH = true;
    io.Fonts->AddFontFromFileTTF(FONT_ICON_FILE_NAME_FAS, 16.0f, &icons_config, icons_ranges);

    //FONT_ICON_FILE_NAME_FAR <-- option 1
    //FONT_ICON_FILE_NAME_FAS <-- option 2
    
    // use FONT_ICON_FILE_NAME_FAR if you want regular instead of solid


	return true;
}

update_status ModuleUi::PreUpdate(float dt)
{
	return UPDATE_CONTINUE;
}

update_status ModuleUi::Update(float dt)
{
    return UPDATE_CONTINUE;
}

update_status ModuleUi::PostUpdate(float dt)
{



    update_status ret = update_status::UPDATE_CONTINUE;

    
    //iterate all different editor panels stored in vector of editorPanels to be able to draw them.
    ImGuiIO& io = ImGui::GetIO();
    (void)io;
    
    //Start Dear ImGui's frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();
    
    if (BeginRootWindow(io, "RootWindow", true, ImGuiWindowFlags_MenuBar))
    {
        bool draw = true;
    
        for (uint i = 0; i < list_ImGuiWindows.size(); ++i)
        {
            if (list_ImGuiWindows[i]->GetIsActive())
            {
                draw = list_ImGuiWindows[i]->Draw(io);
            
                if (!draw)
                {
                    LOG("[UI] Error in %s Window", list_ImGuiWindows[i]->GetName());
                    ret = update_status::UPDATE_STOP;
                    break;
                }
            }
        }
        
        ImGui::End();
    }
    
    RenderImGuiWindows();

    return ret;
}

bool ModuleUi::CleanUp()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

	return true;
}

bool ModuleUi::InitializeImGui() const
{
    bool ret = true;

    // ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    (void)io;

    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable; // Enabling Docking
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable; // Enabling Multi-Viewport / Platform Windows

    // Setting up Dear ImGui style
    ImGui::StyleColorsDark();

    // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
    ImGuiStyle& style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    ImGui_ImplSDL2_InitForOpenGL(App->window->window, App->renderer3D->context);
    ImGui_ImplOpenGL3_Init(0);

    
    return ret;
}

void ModuleUi::AddImGuiWindow(ImGuiWindowBase* window)
{
    list_ImGuiWindows.push_back(window);
}

bool ModuleUi::RenderImGuiWindows() const
{
    ImGuiIO& io = ImGui::GetIO();
    (void)io;

    ImGui::Render();

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        SDL_Window* get_current_window = SDL_GL_GetCurrentWindow();
        SDL_GLContext get_current_context = SDL_GL_GetCurrentContext();

        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();

        SDL_GL_MakeCurrent(get_current_window, get_current_context);
    }

    return true;
}

bool ModuleUi::GetEvent(SDL_Event* event)
{
    return ImGui_ImplSDL2_ProcessEvent(event);
}

bool ModuleUi::BeginRootWindow(ImGuiIO& io, const char* window_id, bool docking, ImGuiWindowFlags window_flags)
{
    bool ret = true;

    ImGuiViewport* viewport = ImGui::GetWindowViewport();

    ImGui::SetNextWindowPos(viewport->Pos);
    ImGui::SetNextWindowSize(viewport->Size);
    ImGui::SetNextWindowViewport(viewport->ID);

    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);

    window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove
        | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus
        | ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoBackground;

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ret = ImGui::Begin(window_id, &ret, window_flags);
    ImGui::PopStyleVar(3); // 1 da error. Mejor poner un 3

    if (docking)
    {
        BeginDockspace(io, window_id, ImGuiDockNodeFlags_PassthruCentralNode);
    }

    return ret;
}

void ModuleUi::BeginDockspace(ImGuiIO& IO, const char* dockspace_id, ImGuiDockNodeFlags docking_flags, ImVec2 size)
{
    if (IO.ConfigFlags & ImGuiConfigFlags_DockingEnable)
    {
        ImGuiID dckspace_id = ImGui::GetID(dockspace_id);
        ImGui::DockSpace(dckspace_id, size, docking_flags);
    }
}

void ModuleUi::AddLogFromModuleUi(const char* str)
{
    if (App->appExit == false && App->moduleUi != nullptr)
    {
        if (consoleWindow != nullptr)
        {
            consoleWindow->AddLogsInConsole(str);
        }
    }

}

void ModuleUi::UpdateFrameData(float frames, float ms)
{
    if (configurationWindow != nullptr)
    {
        // Init window module error for no reason
        configurationWindow->UpdateFrameData(frames, ms);
    }
    
}