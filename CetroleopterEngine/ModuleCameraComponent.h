#ifndef _MODULE_CAMERA_COMPONENT_H_
#define _MODULE_CAMERA_COMPONENT_H_


#include "MathGeoLib.h"
#include "Application.h"
#include "Globals.h"
#include "Component.h"

class ModuleGameObject;

class CameraComponent : public Component
{
public:
	CameraComponent(ModuleGameObject* base);
	~CameraComponent();

	bool Init();
	update_status Update();
	bool CleanUp();

	// ???(varType) GetCameraTransform();
public:
	
	// ???(varType) cameraTransform;

	vec3 X, Y, Z, Position, Reference;

	mat4x4 ViewMatrix, ViewMatrixInverse;

	Frustum frustum;
};


#endif // !_MODULE_CAMERA_COMPONENT_H_

