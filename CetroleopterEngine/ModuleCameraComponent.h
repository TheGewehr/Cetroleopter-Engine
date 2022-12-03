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

	// ??? GetCameraTransform();
public:
	
};


#endif // !_MODULE_CAMERA_COMPONENT_H_

