#include "glew/include/GL/glew.h"
//#include "glew/include/GL/eglew.h"
//#include "glew/include/GL/glxew.h"
//#include "glew/include/GL/wglew.h"
//#include <gl/GL.h>
//#include <gl/GLU.h>


//#pragma comment (lib, "glut/glut32.lib")
#pragma comment (lib, "glew/lib/Release/Win32/glew32.lib")
#pragma comment (lib, "glew/lib/Release/Win32/glew32s.lib")

#include "Globals.h"
#include "Application.h"
#include "ModuleRenderer3D.h"
#include "ModuleModelImport.h"
#include "SDL\include\SDL_opengl.h"
#include <gl/GL.h>
#include <gl/GLU.h>

//#include "imgui.h"
//#include "imgui_impl_opengl3.h"

#pragma comment (lib, "glu32.lib")    /* link OpenGL Utility lib     */
#pragma comment (lib, "opengl32.lib") /* link Microsoft OpenGL lib   */

ModuleRenderer3D::ModuleRenderer3D(bool start_enabled) : Module(start_enabled = true)
{
	
}

// Destructor
ModuleRenderer3D::~ModuleRenderer3D()
{}

// Called before render is available
bool ModuleRenderer3D::Init()
{
	LOG("Creating 3D Renderer context");
	bool ret = true;
	
	//Create context
	context = SDL_GL_CreateContext(App->window->window);
	if(context == NULL)
	{
		LOG("OpenGL context could not be created! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}
	
	if(ret == true)
	{
		//Use Vsync
		if(VSYNC && SDL_GL_SetSwapInterval(1) < 0)
			LOG("Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError());

		//Initialize Projection Matrix
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		//Check for error
		GLenum error = glGetError();
		if(error != GL_NO_ERROR)
		{
			LOG("Error initializing OpenGL! %s\n", gluErrorString(error));
			ret = false;
		}

		//Initialize Modelview Matrix
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		//Check for error
		error = glGetError();
		if(error != GL_NO_ERROR)
		{
			LOG("Error initializing OpenGL! %s\n", gluErrorString(error));
			ret = false;
		}
		
		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
		glClearDepth(1.0f);
		
		//Initialize clear color
		glClearColor(0.f, 0.f, 0.f, 1.f);

		//Check for error
		error = glGetError();
		if(error != GL_NO_ERROR)
		{
			LOG("Error initializing OpenGL! %s\n", gluErrorString(error));
			ret = false;
		}
		
		GLfloat LightModelAmbient[] = {0.0f, 0.0f, 0.0f, 1.0f};
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, LightModelAmbient);
		
		lights[0].ref = GL_LIGHT0;
		lights[0].ambient.Set(0.25f, 0.25f, 0.25f, 1.0f);
		lights[0].diffuse.Set(0.75f, 0.75f, 0.75f, 1.0f);
		lights[0].SetPos(0.0f, 0.0f, 2.5f);
		lights[0].Init();
		
		GLfloat MaterialAmbient[] = {1.0f, 1.0f, 1.0f, 1.0f};
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, MaterialAmbient);

		GLfloat MaterialDiffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, MaterialDiffuse);
		
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		lights[0].Active(true);
		glEnable(GL_LIGHTING);
		glEnable(GL_COLOR_MATERIAL);
	}

	// Projection matrix for
	OnResize(SCREEN_WIDTH, SCREEN_HEIGHT);

	// ImGui Stuff
	//IMGUI_CHECKVERSION();
	//ImGui::CreateContext();
	//ImGui::StyleColorsDark();
	//ImGui_ImplOpenGL3_Init("#version 300 es");
	//
	//ImGui::GetIO();

	//ImGui_ImplOpenGL3_CreateDeviceObjects();
	//ImGui_ImplOpenGL3_CreateFontsTexture();

	//ImGui::BeginMenuBar();
	//ImGui_ImplOpenGL3_NewFrame();
	//ImGui_ImplOpenGL3_RenderDrawData();
	//ImGui_ImplOpenGL3_Shutdown();
	

	
	//ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_None);
	//ImGui::SetNextWindowSize(ImVec2(100.0f, 100.0f), ImGuiCond_None);
	//ImGui::BeginPopupContextWindow();
	//float height = ImGui::GetWindowHeight();

	

	//ImGui::ShowDemoWindow(false);

	//ImGui::Begin("Window A", false, ImGuiWindowFlags_MenuBar);
	//ImGui::Text("This is window A");
	//ImGui::End();
	//
	//ImGui::NewFrame();

	//ImGui::Begin("Window B");
	//ImGui::Text("This is window B");
	//ImGui::End();
	//
	//ImGui::Begin("Window A");
	//ImGui::Button("Button on window A");
	//ImGui::End();
	//
	//ImGui::Begin("Window B");
	//ImGui::Button("Button on window B");
	//ImGui::End();



	GLenum error = glewInit();
	if (GLEW_OK != error)
	{
		LOG("Glew failed, Error: %s\n", glewGetErrorString(error));
	}
	LOG("Glew version: %s\n", glewGetString(GLEW_VERSION));

	glGenBuffers(1, &IndexBuffer);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	
	

	// ..:: Initialization code :: ..
	// 1. bind Vertex Array Object
	glBindVertexArray(ObjectBuffer);
	// 2. copy our vertices array in a vertex buffer for OpenGL to use
	glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// 3. copy our index array in a element buffer for OpenGL to use
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	// 4. then set the vertex attributes pointers
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	return ret;
}

// PreUpdate: clear buffer
update_status ModuleRenderer3D::PreUpdate(float dt)
{
	//ImGui::NewFrame();
	//LOG("PUTO ERROR");
	//ImGui::ShowDemoWindow(false);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(App->camera->GetViewMatrix());

	// light 0 on cam pos
	lights[0].SetPos(App->camera->Position.x, App->camera->Position.y, App->camera->Position.z);

	for(uint i = 0; i < MAX_LIGHTS; ++i)
		lights[i].Render();

	

	return UPDATE_CONTINUE;
}

update_status ModuleRenderer3D::Update(float dt)
{


	if (wireframeMode == false)
	{
		// Turns on wiremode
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	else if (wireframeMode == true)
	{
		// Turns off wiremode
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}

	if (faceCullingMode == false)
	{
		// Turns on wiremode
		glDisable(GL_CULL_FACE);
	}
	else if (faceCullingMode == true)
	{
		// Turns off wiremode
		glEnable(GL_CULL_FACE);
	}

	return UPDATE_CONTINUE;
}

// PostUpdate present buffer to screen
update_status ModuleRenderer3D::PostUpdate(float dt)
{
	//glBegin(GL_TRIANGLES);
	//glColor3f(1.f, 0.f, 0.f);
	//glVertex3f(0.f, 0.f, 0.f);
	//glVertex3f(1.f, 0.f, 0.f);
	//glVertex3f(0.f, 1.f, 0.f);
	//// glVertex3f(0.f, 0.f, 10.f);
	////glNormal3f(0.f,0.f,1.f);
	////glTexCoord3();
	////glTexCoord3f(0.f, 0.f, 1.f);
	//glEnd();
	//LOG("PUTO ERROR");
	//glBegin(GL_TRIANGLES);
	//glColor3f(0.f, 1.f, 0.f);
	//glVertex3f(1.f, 1.f, 0.f);
	//glVertex3f(0.f, 1.f, 0.f);
	//glVertex3f(1.f, 0.f, 0.f);
	//glEnd();
	//
	//glBegin(GL_TRIANGLES);
	//glColor3f(0.f, 0.f, 1.f);
	//glVertex3f(1.f, 1.f, -1.f);
	//glVertex3f(1.f, 1.f, 0.f);
	//glVertex3f(1.f, 0.f, 0.f);
	//glEnd();

	//DDCube_BadIndices();
	
	//glGenBuffers(1, (GLuint*)&(firstBuffer));
	//glBindBuffer(GL_ARRAY_BUFFER, firstBuffer);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 8 * 3, vertices, GL_STATIC_DRAW);
	
	//glEnableClientState(GL_VERTEX_ARRAY);
	//glBindBuffer(GL_ARRAY_BUFFER, firstBuffer); 
	//glVertexPointer(3, GL_FLOAT, 0, NULL);
	// … bind and use other buffers
	//glDrawArrays(GL_TRIANGLES, 0,8);
	//glDisableClientState(GL_VERTEX_ARRAY);
	// 
// activate and specify pointer to vertex array
	//glEnableClientState(GL_VERTEX_ARRAY);
	//glVertexPointer(3, GL_FLOAT, 0, (GLfloat*)&vertices);
	//
	//// draw a cube
	//glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, (GLubyte*)indices);
	//
	//// deactivate vertex arrays after drawing
	//glDisableClientState(GL_VERTEX_ARRAY);
	
	// ..:: Drawing code (in render loop) :: ..
	/*glUseProgram(shaderProgram);
	glBindVertexArray(ObjectBuffer);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);*/

	RenderModels();

	// This must be the last line
	SDL_GL_SwapWindow(App->window->window);

	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleRenderer3D::CleanUp()
{
	LOG("Destroying 3D Renderer");

	

	SDL_GL_DeleteContext(context);
	
	return true;
}


void ModuleRenderer3D::OnResize(int width, int height)
{
	glViewport(0, 0, width, height);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	ProjectionMatrix = perspective(60.0f, (float)width / (float)height, 0.125f, 512.0f);
	glLoadMatrixf(&ProjectionMatrix);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void ModuleRenderer3D::RenderModels()
{
	for (int i = 0; i < App->modelImport->meshes.size(); i++)
	{
		// Draw elements
		MeshVertexData* vertexData = &App->modelImport->meshes[i];
		{
			glEnableClientState(GL_VERTEX_ARRAY);

			// Render things in Element mode
			glBindBuffer(GL_ARRAY_BUFFER, vertexData->id_vertex);
			glVertexPointer(3, GL_FLOAT, 0, NULL);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertexData->id_index);
			glDrawElements(GL_TRIANGLES, vertexData->num_indices, GL_UNSIGNED_INT, NULL);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glDisableClientState(GL_VERTEX_ARRAY);
		}
	}
}

