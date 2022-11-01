#ifndef _MODULE_TRANSFORM_COMPONENT_H_
#define _MODULE_TRANSFORM_COMPONENT_H_


#include "MathGeoLib.h"
#include "Application.h"
#include "Globals.h"
#include "ModuleGameObject.h"

struct GameObject;

class TransformComponent
{
public:
	TransformComponent();
	~TransformComponent();

	float3 GetPosition()const;
	Quat GetRotation()const;
	float3 GetScale()const;

	//World transforms
	std::vector <float3> GetWorldPosition();
	std::vector <Quat> GetWorldRotation();
	std::vector <float3> GetWorldEulerRotation();
	std::vector <float3> GetWorldScale();

	void SetPosition(float x, float y, float z);
	void SetRotation(float x, float y, float z, float w);
	void SetScale(float x, float y, float z);

	std::vector <float4x4> GetWorldTransform();
	void SetWorldTransform(std::vector <float4x4>& worldTransform);

	std::vector <float4x4> GetLocalTransform()const;
	void SetLocalTransform(std::vector <float4x4>& localTransform);

	float3 GetLocalEulerRotation()const;
	void SetLocalEulerRotation(float3 euler);

	void SetChildsAsDirty();

	void SetWorldPosition(const float3& new_position);
	void SetWorldRotation(const Quat& new_rotation);
	void SetWorldRotation(const float3& new_rotation);
	void SetWorldScale(const float3& new_scale);

private:
	void UpdateLocalTransform();
	void UpdateWorldTransform();
	void SyncLocalToWorld();

	float3 position;
	Quat rotation;
	float3 scale;

	std::vector <float4x4> localTransform;
	std::vector <float4x4> worldTransform;

	float3 localEulerRotation;

	bool updateWorld;

	GameObject owner;

};


#endif // !_MODULE_TRANSFORM_COMPONENT_H_

