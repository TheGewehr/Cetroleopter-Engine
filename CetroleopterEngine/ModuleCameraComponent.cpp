#include "ModuleCameraComponent.h"
#include "ModuleGameObject.h"
#include "Component.h"
//#include "mathGeoLib/Geometry/Frustum.h"

CameraComponent::CameraComponent(ModuleGameObject* base) : Component(base, ComponentTypes::CAMERA, "Camera")
{
	frustum.type = PerspectiveFrustum;
	frustum.handedness = FrustumHandedness::FrustumLeftHanded;

	X = vec3(1.0f, 0.0f, 0.0f);
	Y = vec3(0.0f, 1.0f, 0.0f);
	Z = vec3(0.0f, 0.0f, 1.0f);

	Position = vec3(0.0f, 00.0f, 5.0f);
	Reference = vec3(0.0f, 0.0f, 0.0f);

	frustum.pos = float3(Position.x, Position.y, Position.z);
	frustum.front = float3(Z.x, Z.y, Z.z);
	frustum.up = float3(Y.x, Y.y, Y.z);

	frustum.nearPlaneDistance = 1.0f;
	frustum.farPlaneDistance = 100;
	frustum.verticalFov = 60 * DEGTORAD;
	frustum.horizontalFov = 2.0f * atan(tan(frustum.verticalFov * 0.5f) * (SCREEN_WIDTH / SCREEN_HEIGHT));
}

CameraComponent::~CameraComponent()
{
	
}

bool CameraComponent::Init()
{


	return true;
}

update_status CameraComponent::Update()
{
	//frustum.verticalFov = fov * DEGTORAD;
	//frustum.horizontalFov = 2.f * atan(tan(frustum.verticalFov * 0.5f) * (SCREEN_WIDTH / SCREEN_HEIGHT));

	//if (gameObject != nullptr)
	//{
	//	vec3 pos = gameObject->transform->transformWorld.translation();
	//	mat4x4 rot = gameObject->transform->rotationLocal;
	//
	//	X = vec3(rot[0], rot[1], rot[2]);
	//	Y = vec3(rot[4], rot[5], rot[6]);
	//	Z = vec3(rot[8], rot[9], rot[10]);
	//
	//	Position = pos;
	//}

	//frustum.pos = float3(Position.x, Position.y, Position.z);
	//frustum.front = float3(Z.x, Z.y, Z.z);
	//frustum.up = float3(Y.x, Y.y, Y.z);

	//frustum.GetCornerPoints(bboxPoints);

	DrawBoundingBox(bboxPoints, frustumColor);

	return UPDATE_CONTINUE;
}

bool CameraComponent::CleanUp()
{


	return true;
}

void CameraComponent::DrawBoundingBox(float3* corners, Color color)
{

}
