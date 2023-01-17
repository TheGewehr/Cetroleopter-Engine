#include "Globals.h"
#include "Application.h"
#include "ModuleCamera3D.h"
#include <MathGeoLib.h>
#include "ModuleCameraComponent.h"
#include "ModuleMeshComponent.h"
#include "ModuleTransformComponent.h"

ModuleCamera3D::ModuleCamera3D(bool start_enabled) : Module(start_enabled = true)
{

	mainCamera = new CameraComponent(nullptr);
	CalculateViewMatrix();

	mainCamera->X = vec3(1.0f, 0.0f, 0.0f);
	mainCamera->Y = vec3(0.0f, 1.0f, 0.0f);
	mainCamera->Z = vec3(0.0f, 0.0f, 1.0f);

	mainCamera->Position = vec3(-35.0f, 20.0f, 75.0f);
	mainCamera->Reference = vec3(-10.0f, 50.0f, 0.0f);
	isMainCameraMooving = false;

	updateCameraView = false;
	
}

ModuleCamera3D::~ModuleCamera3D()
{}

// -----------------------------------------------------------------
bool ModuleCamera3D::Start()
{
	LOG("Setting up the camera");
	bool ret = true;

	mainCamera->frustum.nearPlaneDistance = 2;
	mainCamera->frustum.farPlaneDistance = 20;
	mainCamera->frustum.verticalFov = 60 * DEGTORAD;
	mainCamera->frustum.horizontalFov = 60;


	return ret;
}

// -----------------------------------------------------------------
bool ModuleCamera3D::CleanUp()
{
	LOG("Cleaning camera");

	return true;
}

// -----------------------------------------------------------------
update_status ModuleCamera3D::Update(float dt)
{

	// Implement a debug camera with keys and mouse
	// Now we can make this movememnt frame rate independant!

	vec3 newPos(0,0,0);
	float speed = 32.0f * dt;
	if(App->input->GetKey(SDL_SCANCODE_LSHIFT) == KEY_REPEAT)
		speed = 100.0f * dt;

	if (App->input->GetKey(SDL_SCANCODE_R) == KEY_REPEAT) newPos.y += speed; isMainCameraMooving = true;
	if (App->input->GetKey(SDL_SCANCODE_F) == KEY_REPEAT) newPos.y -= speed; isMainCameraMooving = true;

	if(App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT) newPos -= mainCamera->Z * speed; isMainCameraMooving = true;
	if(App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT) newPos += mainCamera->Z * speed; isMainCameraMooving = true;


	if(App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) newPos -= mainCamera->X * speed; isMainCameraMooving = true;
	if(App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) newPos += mainCamera->X * speed; isMainCameraMooving = true;

	if (App->input->GetMouseZ() > 0)
	{
		// dezoom
		newPos -= mainCamera->Z * 100;
		isMainCameraMooving = true;

	}
	if (App->input->GetMouseZ() < 0)
	{
		//zoom
		newPos += mainCamera->Z * 100;
		isMainCameraMooving = true;

	}

	mainCamera->Position += newPos;
	mainCamera->Reference += newPos;

	// Mouse motion ----------------

	if (mousePickExpFeatureActivated == true)
	{
		if (App->input->GetMouseButton(SDL_BUTTON_LEFT) == KEY_DOWN && App->input->GetKey(SDL_SCANCODE_LALT) == KEY_IDLE)
		{
			MakeRayCast();
		}
	}

	if ((App->input->GetKey(SDL_SCANCODE_LALT) == KEY_REPEAT))
	{
		isMainCameraMooving = true;
		if ((App->input->GetMouseButton(SDL_BUTTON_LEFT) == KEY_REPEAT))
		{

			
			int dx = -App->input->GetMouseXMotion();
			int dy = -App->input->GetMouseYMotion();

			float Sensitivity = 0.25f;

			mainCamera->Position -= mainCamera->Reference;

			if (dx != 0)
			{
				float DeltaX = (float)dx * Sensitivity;

				mainCamera->X = rotate(mainCamera->X, DeltaX, vec3(0.0f, 1.0f, 0.0f));
				mainCamera->Y = rotate(mainCamera->Y, DeltaX, vec3(0.0f, 1.0f, 0.0f));
				mainCamera->Z = rotate(mainCamera->Z, DeltaX, vec3(0.0f, 1.0f, 0.0f));
			}

			if (dy != 0)
			{
				float DeltaY = (float)dy * Sensitivity;

				mainCamera->Y = rotate(mainCamera->Y, DeltaY, mainCamera->X);
				mainCamera->Z = rotate(mainCamera->Z, DeltaY, mainCamera->X);

				if (mainCamera->Y.y < 0.0f)
				{
					mainCamera->Z = vec3(0.0f, mainCamera->Z.y > 0.0f ? 1.0f : -1.0f, 0.0f);
					mainCamera->Y = cross(mainCamera->Z, mainCamera->X);
				}
			}

			mainCamera->Position = mainCamera->Reference + mainCamera->Z * length(mainCamera->Position);
		}
	}

	
	if (!updateCameraView)
	{
		if (App->input->GetKey(SDL_SCANCODE_R) != KEY_REPEAT)
			if (App->input->GetKey(SDL_SCANCODE_F) != KEY_REPEAT)
	
				if (App->input->GetKey(SDL_SCANCODE_W) != KEY_REPEAT)
					if (App->input->GetKey(SDL_SCANCODE_S) != KEY_REPEAT)
	
	
						if (App->input->GetKey(SDL_SCANCODE_A) != KEY_REPEAT)
							if (App->input->GetKey(SDL_SCANCODE_D) != KEY_REPEAT)
								if ((App->input->GetKey(SDL_SCANCODE_LALT) != KEY_REPEAT))
									if (App->input->GetMouseZ() == 0)
										isMainCameraMooving = false;
		
	}
	else
	{
	
	}

	// Recalculate matrix -------------
	CalculateViewMatrix();

	return UPDATE_CONTINUE;
}

// -----------------------------------------------------------------
void ModuleCamera3D::Look(const vec3 &Position, const vec3 &Reference, bool RotateAroundReference)
{
	this->mainCamera->Position = Position;
	this->mainCamera->Reference = Reference;

	mainCamera->Z = normalize(Position - Reference);
	mainCamera->X = normalize(cross(vec3(0.0f, 1.0f, 0.0f), mainCamera->Z));
	mainCamera->Y = cross(mainCamera->Z, mainCamera->X);

	if(!RotateAroundReference)
	{
		this->mainCamera->Reference = this->mainCamera->Position;
		this->mainCamera->Position += mainCamera->Z * 0.05f;
	}

	CalculateViewMatrix();
}

// -----------------------------------------------------------------
void ModuleCamera3D::LookAt( const vec3 &Spot)
{
	mainCamera->Reference = Spot;

	mainCamera->Z = normalize(mainCamera->Position - mainCamera->Reference);
	mainCamera->X = normalize(cross(vec3(0.0f, 1.0f, 0.0f), mainCamera->Z));
	mainCamera->Y = cross(mainCamera->Z, mainCamera->X);

	CalculateViewMatrix();
}


// -----------------------------------------------------------------
void ModuleCamera3D::Move(const vec3 &Movement)
{
	mainCamera->Position += Movement;
	mainCamera->Reference += Movement;

	CalculateViewMatrix();
}

// -----------------------------------------------------------------
float* ModuleCamera3D::GetViewMatrix()
{
	return &mainCamera->ViewMatrix;
}

void ModuleCamera3D::MakeRayCast()
{

	float tabWidth = App->window->GetWidth(); // Replace with tab window witdh when tabs created
	float tabHeight = App->window->GetHeight(); // Replace with tab window height when tabs created

	float2 screenMousePos = float2((float)App->window->GetWidth() - App->input->GetMouseX() - 500, (float)App->window->GetHeight() - (float)App->input->GetMouseY() + 50);
	float2 normScreenPos = float2(screenMousePos.x / tabWidth, screenMousePos.y / tabHeight);
	float2 worldMousePos = float2(normScreenPos.x * (float)App->window->GetWidth(), normScreenPos.y * (float)App->window->GetHeight());

	float normalizedX = (worldMousePos.x / App->window->GetWidth() - 0.5f) * 2;
	float normalizedY = (worldMousePos.y / App->window->GetHeight() - 0.5f) * 2;
	//float normalizedY = -(worldMousePos.y / App->window->GetHeight() - 0.5f) * 2;

	LineSegment picking = mainCamera->frustum.UnProjectLineSegment(normalizedX, normalizedY);
	

	//Object part
	for (uint i = 0; i < App->scene_intro->gameObjects.size(); i++)
	{
		if (picking.Intersects(App->scene_intro->gameObjects[i]->GetMeshComponent()->bbox))
		{
			App->scene_intro->gameObjects[i]->SelectObject();
		}
	}
}

bool ModuleCamera3D::SaveRequest()
{
	
	this->mainCamera->SaveRequest(true, -1);

	return true;
}

bool ModuleCamera3D::LoadRequest()
{
	this->mainCamera->LoadRequest(true, -1);
	updateCameraView = true;

	return true;
}

// -----------------------------------------------------------------
void ModuleCamera3D::CalculateViewMatrix()
{
	mainCamera->ViewMatrix = mat4x4(mainCamera->X.x, mainCamera->Y.x, mainCamera->Z.x, 0.0f, mainCamera->X.y, mainCamera->Y.y, mainCamera->Z.y, 0.0f, mainCamera->X.z, mainCamera->Y.z, mainCamera->Z.z, 0.0f, -dot(mainCamera->X, mainCamera->Position), -dot(mainCamera->Y, mainCamera->Position), -dot(mainCamera->Z, mainCamera->Position), 1.0f);
	mainCamera->ViewMatrixInverse = inverse(mainCamera->ViewMatrix);
}
