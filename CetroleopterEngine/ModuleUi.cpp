#include "ModuleUi.h"
#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRenderer3D.h"
#include "Application.h"
//#include "OpenGL.h"

#include "SDL/include/SDL_opengl.h"
#include <gl/GL.h>
#include <gl/GLU.h>

#include "Globals.h"

#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_impl_sdl.h"

ModuleUi::ModuleUi(bool start_enabled) : Module(start_enabled)
{
}

ModuleUi::~ModuleUi()
{
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
    ImGui_ImplOpenGL3_NewFrame();//               <--- (asertion error)
    ImGui_ImplSDL2_NewFrame();//                  <--- (linker error)
    ImGui::NewFrame();//                          <--- (asertion error)

    // Content
    

   // ImGui::Render();


	return UPDATE_CONTINUE;
}

bool ModuleUi::CleanUp()
{
    ImGui_ImplOpenGL3_Shutdown();//                  <--- (asertion error)
    ImGui_ImplSDL2_Shutdown();//                     <--- (linker error)
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

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
    ImGuiStyle& style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    ImGui_ImplSDL2_InitForOpenGL(App->window->window, App->renderer3D->context);//           <--- (linker error)
    ImGui_ImplOpenGL3_Init(0);

    
    return ret;
}