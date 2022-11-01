#include "ModuleTransformComponent.h"
#include "ModuleGameObject.h"

TransformComponent::TransformComponent()
{
	updateWorld = false;

	for (int i = 0; i < owner.parent->meshes.size(); i++)
	{
		localTransform[i] = float4x4::identity;
		worldTransform[i] = float4x4::identity;

		localTransform[i].Decompose(position, rotation, scale);
	}
	
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

std::vector <float3> TransformComponent::GetWorldPosition()
{
	if (updateWorld)
		UpdateWorldTransform();

	const int dummyValue = (int)worldTransform.size();

	float3 dummy[dummyValue];

	for (int i = 0; i < worldTransform.size(); i++)
	{
		dummy[i] = worldTransform[i].TranslatePart();
	}

	return dummy;
}

std::vector <Quat> TransformComponent::GetWorldRotation()
{
	if (updateWorld)
		UpdateWorldTransform();

	const int dummyValue = (int)worldTransform.size();

	Quat dummy[dummyValue];

	for (int i = 0; i < worldTransform.size(); i++)
	{
		dummy[i] = worldTransform[i].RotatePart();
	}

	return dummy;
}

std::vector <float3> TransformComponent::GetWorldEulerRotation()
{
	if (updateWorld)
		UpdateWorldTransform();

	const int dummyValue = (int)worldTransform.size();

	float3 dummy[dummyValue];

	for (int i = 0; i < worldTransform.size(); i++)
	{
		dummy[i] = RadToDeg(worldTransform[i].RotatePart().ToEulerXYZ());
	}

	return dummy;
}

std::vector <float3> TransformComponent::GetWorldScale()
{
	if (updateWorld)
		UpdateWorldTransform();

	const int dummyValue = (int)worldTransform.size();

	float3 dummy[dummyValue];

	for (int i = 0; i < worldTransform.size(); i++)
	{
		dummy[i] = worldTransform[i].GetScale();
	}

	return dummy;
}

std::vector <float4x4> TransformComponent::GetWorldTransform()
{
	if (updateWorld)
		UpdateWorldTransform();

	return worldTransform;
}

void TransformComponent::SetWorldTransform(std::vector <float4x4>& worldTransform)
{
	this->worldTransform = worldTransform;

	SyncLocalToWorld();
}

std::vector <float4x4> TransformComponent::GetLocalTransform() const
{
	return localTransform;
}

void TransformComponent::SetLocalTransform(std::vector <float4x4>& localTransform)
{
	for (int i = 0; i < localTransform.size(); i++)
	{
		this->localTransform[i] = localTransform[i];
		localTransform[i].Decompose(position, rotation, scale);
		localEulerRotation = localTransform[i].RotatePart().ToEulerXYZ();
	}

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

	/*for (uint i = 0; i < owner.children.size(); ++i)
	{
		TransformComponent* childTransform = owner.children[i]->GetComponent<TransformComponent>();

		if (childTransform != nullptr)
		{
			childTransform->updateWorld = true;
			childTransform->SetChildsAsDirty();
		}
	}*/
}

void TransformComponent::SetWorldPosition(const float3& newPosition)
{
	for (int i = 0; i < owner.parent->meshes.size(); i++)
	{
		worldTransform[i].SetTranslatePart(newPosition);
	}

	SyncLocalToWorld();
}

void TransformComponent::SetWorldRotation(const Quat& newRotation)
{
	for (int i = 0; i < owner.parent->meshes.size(); i++)
	{
		worldTransform[i].SetRotatePart(newRotation);
	}

	SyncLocalToWorld();
}

void TransformComponent::SetWorldRotation(const float3& new_rotation)
{
	for (int i = 0; i < owner.parent->meshes.size(); i++)
	{
		worldTransform[i].SetRotatePart(Quat::FromEulerXYZ(new_rotation.x, new_rotation.y, new_rotation.z));
	}

	SyncLocalToWorld();
}

void TransformComponent::SetWorldScale(const float3& newScale)
{
	for (int i = 0; i < owner.parent->meshes.size(); i++)
	{
		worldTransform[i].Scale(worldTransform[i].GetScale().Neg());

		if (newScale.x == 0.0f || newScale.y == 0.0f || newScale.z == 0.0f)
		{
			worldTransform[i].Scale(float3(0.1f, 0.1f, 0.1f));
		}
		else
		{
			worldTransform[i].Scale(newScale);
		}
	}

	SyncLocalToWorld();
}

void TransformComponent::UpdateLocalTransform()
{
	for (int i = 0; i < owner.parent->meshes.size(); i++)
	{
		localTransform[i] = float4x4::FromTRS(position, rotation, scale);
	}

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

	//worldTransform = (owner.parent != nullptr) ? owner.parent->GetComponent<TransformComponent>()->worldTransform * localTransform : localTransform;

	if (owner.parent != nullptr)
	{
		for (int i = 0; i < owner.parent->meshes.size(); i++)
		{
			worldTransform[i] = owner.parent->meshes[i].transform->worldTransform[i] * localTransform[i];
		}
	}
	else
	{
		for (int i = 0; i < owner.parent->meshes.size(); i++)
		{
			worldTransform[i] = localTransform[i];
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

	//localTransform = (owner.parent != nullptr) ? owner.parent->GetComponent<TransformComponent>()->worldTransform.Inverted() * worldTransform : worldTransform;
	if (owner.parent != nullptr)
	{
		for (int i = 0; i < owner.parent->meshes.size(); i++)
		{
			localTransform[i] = owner.parent->meshes[i].transform->worldTransform[i].Inverted() * worldTransform[i];
		}
	}
	else
	{
		for (int i = 0; i < owner.parent->meshes.size(); i++)
		{
			localTransform[i] = worldTransform[i];
		}
	}
	
	
	for (int i = 0; i < localTransform.size(); i++)
	{
		SetLocalTransform(localTransform[i]);
	}

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
