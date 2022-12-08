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
	void UpdateGameObjectCamera(ModuleGameObject gameObject);
	void DrawBoundingBox(float3* corners, Color color);

	bool SaveRequest(bool isMainCamera , int positionInList);
	bool LoadRequest(bool isMainCamera, int positionInList);

public:
	
	// ???(varType) cameraTransform;

	vec3 X, Y, Z, Position, Reference;

	mat4x4 ViewMatrix, ViewMatrixInverse;
	float fov = 60;

	Frustum frustum;
	vec bboxPoints[8];
	Color frustumColor = Color(1, 0, 0, 1);
};


#endif // !_MODULE_CAMERA_COMPONENT_H_

