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

	void DrawBoundingBox(float3* corners, Color color);
public:
	
	// ???(varType) cameraTransform;

	vec3 X, Y, Z, Position, Reference;

	mat4x4 ViewMatrix, ViewMatrixInverse;
	float fov = 60;

	Frustum frustum;
	vec bboxPoints[8];
	Color frustumColor = Color(0, 1, 0, 1);
};


#endif // !_MODULE_CAMERA_COMPONENT_H_

