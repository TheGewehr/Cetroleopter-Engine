#include "glew/include/GL/glew.h"

#include "SDL/include/SDL_opengl.h"
#include <gl/GL.h>
#include <gl/GLU.h>

#include "Globals.h"

#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_impl_sdl.h"


#include "ModuleUi.h"
#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRenderer3D.h"
//#include "OpenGL.h"

#include "ImGuiWindow.h"
#include "ConfigurationWindow.h"

ModuleUi::ModuleUi(bool start_enabled) : Module(start_enabled),
configurationWindow(new ConfigurationWindow("ConfigurationWindow"))
{
   // AddImGuiWindow(configurationWindow);
}

ModuleUi::~ModuleUi()
{
   //std::vector<ImGuiWindow*>::reverse_iterator item = list_ImGuiWindows.rbegin();
   //while (item != list_ImGuiWindows.rend())
   //{
   //    (*item)->CleanUp();
   //    delete *item;
   //    ++item;
   //}
}

bool ModuleUi::Start()
{
    InitializeImGui();

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

    
    ////iterate all different editor panels stored in vector of editorPanels to be able to draw them.
    //ImGuiIO& IO = ImGui::GetIO();
    //(void)IO;
    //
    ////Start Dear ImGui's frame
    //ImGui_ImplOpenGL3_NewFrame();
    //ImGui_ImplSDL2_NewFrame();
    //ImGui::NewFrame();
    //
    //if (BeginRootWindow(IO, "RootWindow", true, ImGuiWindowFlags_MenuBar))
    //{
    //    bool draw = true;
    //
    //    for (uint i = 0; i < list_ImGuiWindows.size(); ++i)
    //    {
    //        if (list_ImGuiWindows[i]->GetIsActive())
    //        {
    //            draw = list_ImGuiWindows[i]->Draw(IO);
    //        
    //            if (!draw)
    //            {
    //                ret = update_status::UPDATE_STOP;
    //                break;
    //            }
    //        }
    //    }
    //    ImGui::End();
    //}
    //
    //RenderImGuiWindows();

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();

   

    ImGui::Render();
    ImGui::EndFrame();
    ImGui::UpdatePlatformWindows();

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

//void ModuleUi::AddImGuiWindow(ImGuiWindow* window)
//{
//    list_ImGuiWindows.push_back(window);
//}

bool ModuleUi::RenderImGuiWindows() const
{
    ImGuiIO& IO = ImGui::GetIO();
    (void)IO;

    ImGui::Render();

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    if (IO.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        SDL_Window* backup_current_window = SDL_GL_GetCurrentWindow();
        SDL_GLContext backup_current_context = SDL_GL_GetCurrentContext();

        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();

        SDL_GL_MakeCurrent(backup_current_window, backup_current_context);
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
    ImGui::PopStyleVar(1); // 1 as default value, for testing purposes

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

