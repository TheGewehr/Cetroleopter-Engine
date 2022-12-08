#include "ModuleMeshComponent.h"
#include "ModuleGameObject.h"
#include "Component.h"

MeshComponent::MeshComponent(ModuleGameObject* base) : Component(base, ComponentTypes::MESH, "Mesh")
{
	//glBufferData(GL_ARRAY_BUFFER, bb_vertices.size() * sizeof(BB_Vertex), &bb_vertices[0], GL_STATIC_DRAW);
	////set bbox
	//base->aabb.SetNegativeInfinity();
	//float3* bboxVertices = new float3[sizeof(float3) * bb_vertices.size()];
	//
	//for (size_t i = 0; i < bb_vertices.size(); i++)
	//{
	//	float3 vec;
	//	vec.x = bb_vertices[i].Position.x;
	//	vec.y = bb_vertices[i].Position.y;
	//	vec.z = bb_vertices[i].Position.z;
	//
	//
	//	bboxVertices[i] = vec;
	//
	//	float3 v = float3(bboxVertices[i]);
	//	//printf("%f %f %f \n", v.x, v.y, v.z);
	//}
	//
	//
	//
	//base->aabb.Enclose(bboxVertices, bb_vertices.size());
	//base->aabb.GetCornerPoints(bboxPoints);
	//
	//delete[] bboxVertices;

	meshPath = mesh.path.c_str();
}

MeshComponent::~MeshComponent()
{
	
}

bool MeshComponent::Init()
{


	return true;
}

update_status MeshComponent::Update()
{


	return UPDATE_CONTINUE;
}

bool MeshComponent::CleanUp()
{


	return true;
}

bool MeshComponent::SaveComponent(int positionInList)
{
	std::string listPosition = std::to_string(positionInList);
	meshPath = mesh.path.c_str();
	json_object_dotset_string(json_object(App->save_load->sceneFile), std::string("Scene01.GameObjectsList." + listPosition + ".MeshComponent.Path").c_str(), meshPath);

	return false;
}

bool MeshComponent::LoadComponent()
{
	meshPath = json_object_dotget_string(json_object(App->save_load->sceneFile), "Scene01.GameObjectsList.ID.MeshComponent.Path");

	return false;
}


