#ifndef _MODULE_CAMERA_H_
#define _MODULE_CAMERA_H_

#include "Module.h"
#include "Globals.h"
#include "glmath.h"
//#include "ModuleCameraComponent.h"

class CameraComponent;

class ModuleCamera3D : public Module
{
public:
	ModuleCamera3D(bool start_enabled = true);
	~ModuleCamera3D();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

	void Look(const vec3 &Position, const vec3 &Reference, bool RotateAroundReference = false);
	void LookAt(const vec3 &Spot);
	void Move(const vec3 &Movement);
	float* GetViewMatrix();

	void MakeRayCast();

	bool SaveRequest();
	bool LoadRequest();

private:

	void CalculateViewMatrix();

public:
	
	//vec3 X, Y, Z, Position, Reference; <-- Inside mainCamera as camera component
	CameraComponent* mainCamera;

	bool isMainCameraMooving;
	bool updateCameraView;

	bool mousePickExpFeatureActivated = false;
	bool transformExpFeatureActivated = false;

private:

	
	//mat4x4 ViewMatrix, ViewMatrixInverse; <-- Inside mainCamera as camera component
};

#endif // !_MODULE_CAMERA_H_