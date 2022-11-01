#include "ModuleTransformComponent.h"
#include "ModuleGameObject.h"

TransformComponent::TransformComponent()
{
	updateWorld = false;	

	for (int i = 0; i < App->moduleGameObject->objects.size(); i++)
	{
		for (int j = 0; j < App->moduleGameObject->objects[i].meshes.size(); j++)
		{
			if (App->moduleGameObject->objects[i].meshes[j].transform == this)
			{
				owner = App->moduleGameObject->objects[i];

				position = { 0,0,0 };
				
			}
		}
	}

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
	for (int i = 0; i < App->moduleGameObject->objects.size(); i++)
	{
		for (int j = 0; j < App->moduleGameObject->objects[i].meshes.size(); j++)
		{
			if (App->moduleGameObject->objects[i].meshes[j].transform == this)
			{
				owner = App->moduleGameObject->objects[i];
				i = App->moduleGameObject->objects.size();
				j = App->moduleGameObject->objects[i].meshes.size();
			}
		}
	}
	
	if (owner.children.empty())
		return;
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
	for (int i = 0; i < App->moduleGameObject->objects.size(); i++)
	{
		for (int j = 0; j < App->moduleGameObject->objects[i].meshes.size(); j++)
		{
			if (App->moduleGameObject->objects[i].meshes[j].transform == this)
			{
				owner = App->moduleGameObject->objects[i];
				i = App->moduleGameObject->objects.size();
				j = App->moduleGameObject->objects[i].meshes.size();
			}
		}
	}

	if (owner.parent != nullptr)
	{
		for (int i = 0; i < owner.parent->meshes.size(); i++)
		{
			worldTransform = owner.parent->meshes[i].transform->worldTransform * localTransform;
		}
	}
	else
	{
		for (int i = 0; i < owner.parent->meshes.size(); i++)
		{
			worldTransform = localTransform;
		}
	}
	

	SetChildsAsDirty();

	updateWorld = false;
}

void TransformComponent::SyncLocalToWorld()
{
	for (int i = 0; i < App->moduleGameObject->objects.size(); i++)
	{
		for (int j = 0; j < App->moduleGameObject->objects[i].meshes.size(); j++)
		{
			if (App->moduleGameObject->objects[i].meshes[j].transform == this)
			{
				owner = App->moduleGameObject->objects[i];
				i = App->moduleGameObject->objects.size();
				j = App->moduleGameObject->objects[i].meshes.size();
			}
		}
	}

	if (owner.parent != nullptr)
	{
		for (int i = 0; i < owner.parent->meshes.size(); i++)
		{
			localTransform = owner.parent->meshes[i].transform->worldTransform.Inverted() * worldTransform;
		}
	}
	else
	{
		
		localTransform = worldTransform;
		
	}	
	
	SetLocalTransform(localTransform);	

	SetChildsAsDirty();
}

void TransformComponent::SetPosition(float x, float y, float z)
{
	position.Set(x, y, z);
	UpdateLocalTransform();
}

void TransformComponent::SetRotation(float x, float y, float z, float w)
{
	rotation.Set(x, y, z, w);
	localEulerRotation = rotation.ToEulerXYZ();

	UpdateLocalTransform();
}

void TransformComponent::SetScale(float x, float y, float z)
{
	scale.x = (x != 0.0f) ? x : 0.5f;
	scale.y = (y != 0.0f) ? y : 0.5f;
	scale.z = (z != 0.0f) ? z : 0.5f;

	UpdateLocalTransform();
}
