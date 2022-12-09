#include "glew/include/GL/glew.h"


#pragma comment (lib, "glew/lib/Release/Win32/glew32.lib")
#pragma comment (lib, "glew/lib/Release/Win32/glew32s.lib")

#include "Globals.h"
#include "Application.h"
#include "ModuleRenderer3D.h"
#include "ModuleModelImport.h"
#include "ModuleCamera3D.h"
#include "ModuleGameObject.h"
#include "ModuleTransformComponent.h"
#include "ModuleMeshComponent.h"
#include "ModuleTextureComponent.h"
#include "ModuleTransformComponent.h"
#include "ModuleCameraComponent.h"
#include "Component.h"
#include "SDL\include\SDL_opengl.h"
#include <gl/GL.h>
#include <gl/GLU.h>


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
		if(vsyncEnabled && SDL_GL_SetSwapInterval(1) < 0)
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


	GLenum error = glewInit();
	if (GLEW_OK != error)
	{
		LOG("Glew failed, Error: %s\n", glewGetErrorString(error));
	}
	LOG("Glew version: %s\n", glewGetString(GLEW_VERSION));

	
	return ret;
}

bool ModuleRenderer3D::Start()
{
	
	return true;
}

// PreUpdate: clear buffer
update_status ModuleRenderer3D::PreUpdate(float dt)
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(App->camera->GetViewMatrix());

	// light 0 on cam pos
	lights[0].SetPos(App->camera->mainCamera->Position.x, App->camera->mainCamera->Position.y, App->camera->mainCamera->Position.z);

	for(uint i = 0; i < MAX_LIGHTS; ++i)
		lights[i].Render();

	

	return UPDATE_CONTINUE;
}

update_status ModuleRenderer3D::Update(float dt)
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_AMBIENT);


	if (wireframeMode == false)
	{
		// Turns off wiremode
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	else if (wireframeMode == true)
	{
		// Turns on wiremode
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}

	if (faceCullingMode == false)
	{
		// Turns off wiremode
		glDisable(GL_CULL_FACE);
	}
	else if (faceCullingMode == true)
	{
		// Turns on wiremode
		glEnable(GL_CULL_FACE);
	}

	if (texturesOFF == false)
	{
		// Turns on textures
		glEnable(GL_TEXTURE_2D);
	}
	else if (texturesOFF == true)
	{
		// Turns off textures
		glDisable(GL_TEXTURE_2D);
	}

	if (disableLights == false)
	{
		// Turns on textures
		glEnable(GL_LIGHTING);
	}
	else if (disableLights == true)
	{
		// Turns off textures
		glDisable(GL_LIGHTING);
	}

	if (disableAO == false)
	{
		// Turns on textures
		glEnable(GL_AMBIENT);
	}
	else if (disableAO == true)
	{
		// Turns off textures
		glDisable(GL_AMBIENT);
	}

	return UPDATE_CONTINUE;
}

// PostUpdate present buffer to screen
update_status ModuleRenderer3D::PostUpdate(float dt)
{
	glUseProgram(shaderProgram);
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	// This must be the last line
	SDL_GL_SwapWindow(App->window->window);

	return UPDATE_CONTINUE;
}

void ModuleRenderer3D::SetVsync(bool value)
{
	vsyncEnabled = value;

	if (vsyncEnabled == true)
	{
		if (SDL_GL_SetSwapInterval(1) < 0)
		{
			LOG("Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError());
		}		
	}
	else
	{
		SDL_GL_SetSwapInterval(0);
	}
		
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

void ModuleRenderer3D::RenderGameObjects(ModuleGameObject gameObject, float3 position)
{
	if (gameObject.GetObjectIsActive())
	{
		MeshComponent* meshComponent = (MeshComponent*)gameObject.GetComponentOfType(ComponentTypes::MESH);
		TextureComponent* textureComponent = (TextureComponent*)gameObject.GetComponentOfType(ComponentTypes::TEXTURE);

		if (meshComponent->IsComponentActive())
		{
			if (meshComponent != nullptr)
			{

				if (App->camera->isMainCameraMooving == false)
				{
					glPushMatrix();
					glMultMatrixf((GLfloat*)&gameObject.GetTransformComponent()->GetWorldTransform().Transposed()); // Apply Transformation

				}
				else
				{
					glMultMatrixf((GLfloat*)&gameObject.GetTransformComponent()->GetWorldTransform().Transposed());
				}
				
				glEnableClientState(GL_VERTEX_ARRAY);
				glEnableClientState(GL_TEXTURE_COORD_ARRAY);

				// Render things in Element mode
				glBindBuffer(GL_ARRAY_BUFFER, meshComponent->mesh.id_vertex);
				glVertexPointer(3, GL_FLOAT, 0, NULL);
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, meshComponent->mesh.id_index);
				glEnableClientState(GL_TEXTURE_COORD_ARRAY);
				glBindBuffer(GL_ARRAY_BUFFER, meshComponent->mesh.id_UV);

				if (textureComponent->IsComponentActive())
				{
					if (textureComponent->objectTexture != nullptr)
					{

						glEnableClientState(GL_VERTEX_ARRAY);
						
						// Render things in Element mode
						glBindBuffer(GL_ARRAY_BUFFER, meshComponent->mesh.id_vertex);
						glVertexPointer(3, GL_FLOAT, 0, NULL);
						glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, meshComponent->mesh.id_index);
						
						glEnableClientState(GL_TEXTURE_COORD_ARRAY);
						glBindBuffer(GL_ARRAY_BUFFER, meshComponent->mesh.id_UV);
						glTexCoordPointer(3, GL_FLOAT, 0, NULL);
						glBindTexture(GL_TEXTURE_2D, textureComponent->objectTexture->texture_ID);
						
						glDrawElements(GL_TRIANGLES, meshComponent->mesh.num_indices, GL_UNSIGNED_INT, NULL);
					}
				}

				if (App->renderer3D->checkerTextureON)
				{
					glBindTexture(GL_TEXTURE_2D, checkerTextureID);
				}
				
				glDrawElements(GL_TRIANGLES, meshComponent->mesh.num_indices, GL_UNSIGNED_INT, NULL);

				glBindTexture(GL_TEXTURE_2D, 0);
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
				glBindBuffer(GL_ARRAY_BUFFER, 0);
				glRasterPos3f(position.x, position.y, position.z);

				glDisableClientState(GL_TEXTURE_COORD_ARRAY);
				glDisableClientState(GL_VERTEX_ARRAY);

				
			}
		}
	}
}