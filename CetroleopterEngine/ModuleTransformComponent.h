#ifndef _MODULE_TRANSFORM_COMPONENT_H_
#define _MODULE_TRANSFORM_COMPONENT_H_


#include "MathGeoLib.h"
#include "Application.h"
#include "Globals.h"
//#include "ModuleGameObject.h"
#include "Component.h"

class ModuleGameObject;

class TransformComponent : public Component
{
public:
	TransformComponent(ModuleGameObject* base);
	~TransformComponent();

	float3 GetPosition()const;
	Quat GetRotation()const;
	float3 GetScale()const;

	//World transforms
	float3 GetWorldPosition();
	Quat GetWorldRotation();
	float3 GetWorldEulerRotation();
	float3 GetWorldScale();

	void SetPosition(float x, float y, float z);
	void SetRotation(const float3& newRotation);
	void SetScale(const float3& newScale);

	float4x4 GetWorldTransform();
	void SetWorldTransform(float4x4 worldTransform);

	float4x4 GetLocalTransform()const;
	void SetLocalTransform(float4x4& localTransform);

	float3 GetLocalEulerRotation()const;
	void SetLocalEulerRotation(float3 euler);

	void SetChildsAsDirty();

	void SetWorldPosition(const float3& new_position);
	void SetWorldRotation(const Quat& new_rotation);
	void SetWorldRotation(const float3& new_rotation);
	void SetWorldScale(const float3& new_scale);


	void UpdateLocalTransform();
	void UpdateWorldTransform();
	void SyncLocalToWorld();

	bool SaveComponent(int positionInList);
	bool LoadComponent(int positionInList);

	float3 position;
	Quat rotation;
	float3 scale;

	float4x4 localTransform;
	float4x4 worldTransform;

	float3 localEulerRotation;

	bool updateWorld;

	ModuleGameObject* ComponentOwner;

};


#endif // !_MODULE_TRANSFORM_COMPONENT_H_

