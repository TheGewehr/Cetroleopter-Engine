#include "ModuleTransformComponent.h"
#include "ModuleGameObject.h"
#include "Component.h"

TransformComponent::TransformComponent(ModuleGameObject* base) : Component(base, ComponentTypes::TRANSFORM, "Transform")
{
	/*updateWorld = false;	

	for (int i = 0; i < App->moduleGameObject->objects.size(); i++)
	{
		for (int j = 0; j < App->moduleGameObject->objects[i].meshes.size(); j++)
		{
			if (App->moduleGameObject->objects[i].meshes[j].transform == this)
			{
				base = App->moduleGameObject->objects[i];

				position = { 0,0,0 };
				
			}
		}
	}

	localTransform = float4x4::identity;
	worldTransform = float4x4::identity;

	localTransform.Decompose(position, rotation, scale);

	
	localEulerRotation = rotation.ToEulerXYZ();	*/

	ComponentOwner = base;

	updateWorld = false;
	localTransform = float4x4::identity;
	worldTransform = float4x4::identity;

	localTransform.Decompose(position, rotation, scale);

	localEulerRotation = rotation.ToEulerXYZ();
	
}

TransformComponent::~TransformComponent()
{
	
}


float3 TransformComponent::GetPosition() const
{
	return position;
}

Quat TransformComponent::GetRotation() const
{
	return rotation;
}

float3 TransformComponent::GetScale() const
{
	return scale;
}

float3 TransformComponent::GetWorldPosition()
{
	if (updateWorld)
		UpdateWorldTransform();

	return worldTransform.TranslatePart();
}

Quat TransformComponent::GetWorldRotation()
{
	if (updateWorld)
		UpdateWorldTransform();

	return Quat(worldTransform.RotatePart());
}

float3 TransformComponent::GetWorldEulerRotation()
{
	if (updateWorld)
		UpdateWorldTransform();

	return RadToDeg(worldTransform.RotatePart().ToEulerXYZ());
}

float3 TransformComponent::GetWorldScale()
{
	if (updateWorld)
		UpdateWorldTransform();

	return worldTransform.GetScale();
}

float4x4 TransformComponent::GetWorldTransform()
{
	if (updateWorld)
		UpdateWorldTransform();

	return worldTransform;
}

void TransformComponent::SetWorldTransform(float4x4 worldTransform)
{
	this->worldTransform = worldTransform;

	SyncLocalToWorld();
}

float4x4 TransformComponent::GetLocalTransform() const
{
	return localTransform;
}

void TransformComponent::SetLocalTransform(float4x4& localTransform)
{
	this->localTransform = localTransform;
	localTransform.Decompose(position, rotation, scale);
	localEulerRotation = localTransform.RotatePart().ToEulerXYZ();

	UpdateWorldTransform();
}

float3 TransformComponent::GetLocalEulerRotation() const
{
	return localEulerRotation;
}

void TransformComponent::SetLocalEulerRotation(float3 euler)
{
	this->localEulerRotation = DegToRad(euler);
	rotation = Quat::FromEulerXYZ(localEulerRotation.x, localEulerRotation.y, localEulerRotation.z);

	UpdateLocalTransform();
}

void TransformComponent::SetChildsAsDirty()
{
	/*for (int i = 0; i < App->moduleGameObject->objects.size(); i++)
	{
		for (int j = 0; j < App->moduleGameObject->objects[i].meshes.size(); j++)
		{
			if (App->moduleGameObject->objects[i].meshes[j].transform == this)
			{
				base = App->moduleGameObject->objects[i];
				i = App->moduleGameObject->objects.size();
				j = App->moduleGameObject->objects[i].meshes.size();
			}
		}
	}
	
	if (base.children.empty())
		return;*/


	if (ComponentOwner->childs.empty())
		return;

	

	for (uint i = 0; i < ComponentOwner->childs.size(); ++i)
	{
		TransformComponent* childTransform = ComponentOwner->childs[i]->GetTransformComponent();

		if (childTransform != nullptr)
		{
			childTransform->updateWorld = true;
			childTransform->SetChildsAsDirty();
		}
	}
}

void TransformComponent::SetWorldPosition(const float3& newPosition)
{
	worldTransform.SetTranslatePart(newPosition);

	SyncLocalToWorld();

}

void TransformComponent::SetWorldRotation(const Quat& newRotation)
{
	worldTransform.SetRotatePart(newRotation);

	SyncLocalToWorld();
}

void TransformComponent::SetWorldRotation(const float3& new_rotation)
{
	worldTransform.SetRotatePart(Quat::FromEulerXYZ(new_rotation.x, new_rotation.y, new_rotation.z));

	SyncLocalToWorld();
}

void TransformComponent::SetWorldScale(const float3& newScale)
{
	worldTransform.Scale(worldTransform.GetScale().Neg());

	if (newScale.x == 0.0f || newScale.y == 0.0f || newScale.z == 0.0f)
	{
		worldTransform.Scale(float3(0.1f, 0.1f, 0.1f));
	}
	else
	{
		worldTransform.Scale(newScale);
	}

	SyncLocalToWorld();
}

void TransformComponent::UpdateLocalTransform()
{
	localTransform = float4x4::FromTRS(position, rotation, scale);

	updateWorld = true;
}

void TransformComponent::UpdateWorldTransform()
{

	worldTransform = localTransform;
	//worldTransform = (ComponentOwner->parent != nullptr ) ? ComponentOwner->parent->GetTransformComponent()->worldTransform * localTransform : localTransform;

	SetChildsAsDirty();
	

	updateWorld = false;

	/*C_Camera* c_camera = owner->GetComponent<C_Camera>();
	if (c_camera != nullptr)
	{
		c_camera->UpdateFrustumTransform();
	}*/
}

void TransformComponent::SyncLocalToWorld()
{
	/*for (int i = 0; i < App->moduleGameObject->objects.size(); i++)
	{
		for (int j = 0; j < App->moduleGameObject->objects[i].meshes.size(); j++)
		{
			if (App->moduleGameObject->objects[i].meshes[j].transform == this)
			{
				base = App->moduleGameObject->objects[i];
				i = App->moduleGameObject->objects.size();
				j = App->moduleGameObject->objects[i].meshes.size();
			}
		}
	}

	if (base.parent != nullptr)
	{
		for (int i = 0; i < base.parent->meshes.size(); i++)
		{
			localTransform = base.parent->meshes[i].transform->worldTransform.Inverted() * worldTransform;
		}
	}
	else
	{
		
		localTransform = worldTransform;
		
	}	
	
	SetLocalTransform(localTransform);	

	SetChildsAsDirty();*/

	

	localTransform = (ComponentOwner->parent != nullptr) ? ComponentOwner->parent->GetTransformComponent()->worldTransform.Inverted() * worldTransform : worldTransform;

	SetLocalTransform(localTransform);

	SetChildsAsDirty();

	/*C_Camera* cCamera = owner->GetComponent<C_Camera>();
	if (cCamera != nullptr)
	{
		cCamera->UpdateFrustumTransform();
	}*/
}

void TransformComponent::SetPosition(float x, float y, float z)
{
	position.Set(x, y, z);
	UpdateLocalTransform();
}

void TransformComponent::SetRotation(const float3& newRotation)
{
	rotation = Quat::FromEulerXYZ(newRotation.x, newRotation.y, newRotation.z);
	localEulerRotation = newRotation;

	UpdateLocalTransform();
}

void TransformComponent::SetScale(const float3& newScale)
{
	
	if (newScale.x == 0.0f || newScale.y == 0.0f || newScale.z == 0.0f)
	{
		float3 mod_scale = float3::one;

		mod_scale.x = (newScale.x == 0.0f) ? 0.01f : newScale.x;
		mod_scale.y = (newScale.y == 0.0f) ? 0.01f : newScale.y;
		mod_scale.z = (newScale.z == 0.0f) ? 0.01f : newScale.z;

		scale = mod_scale;
	}
	else
	{
		scale = newScale;
	}

	UpdateLocalTransform();
}
