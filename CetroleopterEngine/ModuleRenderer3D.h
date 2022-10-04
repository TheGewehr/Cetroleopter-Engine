#ifndef _MODULE_RENDERER_H_
#define _MODULE_RENDERER_H_

#include "Module.h"
#include "Globals.h"
#include "glmath.h"
#include "Light.h"
#include <MathGeoLib.h>

#define MAX_LIGHTS 10
//#define GLVertexDD(idx) {float3& v = vertices[*idx - 1]; glVertex3f(v.x, v.y, v.z);}

class ModuleRenderer3D : public Module
{
public:
	ModuleRenderer3D(bool start_enabled = true);
	~ModuleRenderer3D();

	bool Init();
	update_status PreUpdate(float dt);
	update_status PostUpdate(float dt);
	bool CleanUp();

	void OnResize(int width, int height);


	//void DDCube_VecIndices();
	//void DDCube_BadIndices();

public:

	Light lights[MAX_LIGHTS];
	SDL_GLContext context;
	mat3x3 NormalMatrix;
	mat4x4 ModelMatrix, ViewMatrix, ProjectionMatrix;

	//float3 vertices[8] = {
	//{-1., -1., -1.}, {1., -1., -1.},
	//{-1., 1., -1.}, {1., 1., -1.},
	//{-1., -1., 1.}, {1., -1., 1.},
	//{-1., 1., 1.}, {1., 1., 1.}
	//};
	//
	//int indices[36] = {
	//	5,6,8,	5,8,7,
	//	4,2,1,	1,3,4,
	//	4,3,8,	3,7,8,
	//	2,6,1,	1,6,5,
	//	1,7,3,	1,5,7,
	//	2,4,8,	2,8,6
	//};
	//
	//float3 colors[6] = {
	//	{1., 1., 0.}, {1., 0., 1.}, {0., 1., 1.},
	//	{1., 0., 0.}, {0., 1., 0.}, {0., 0., 1.}
	//};

};

#endif // !_MODULE_RENDERER_H_