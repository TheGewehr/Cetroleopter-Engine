#ifndef _MODULE_RENDERER_H_
#define _MODULE_RENDERER_H_

#include "Module.h"
#include "Globals.h"
#include "glmath.h"
#include "Light.h"
#include <MathGeoLib.h>

#define GLVertexDD(idx) {float3& v = vertices[*idx - 1]; glVertex3f(v.x, v.y, v.z);}
#define MAX_LIGHTS 10

class ModuleRenderer3D : public Module
{
public:
	ModuleRenderer3D(bool start_enabled = true);
	~ModuleRenderer3D();

	bool Init();
	update_status PreUpdate(float dt);
	update_status Update(float dt);
	update_status PostUpdate(float dt);
	bool CleanUp();

	void OnResize(int width, int height);

public:

	Light lights[MAX_LIGHTS];
	SDL_GLContext context = NULL;
	mat3x3 NormalMatrix;
	mat4x4 ModelMatrix, ViewMatrix, ProjectionMatrix;
	bool wireframeMode = false;

	float vertices[12] = {
	 0.5f,  0.5f, 0.0f,  // top right
	 0.5f, -0.5f, 0.0f,  // bottom right
	-0.5f, -0.5f, 0.0f,  // bottom left
	-0.5f,  0.5f, 0.0f   // top left 
	};

	unsigned int indices[6] = {  // note that we start from 0!
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};

	unsigned int IndexBuffer;
	unsigned int VertexBuffer;
	unsigned int ObjectBuffer;
	unsigned int shaderProgram;

};

#endif // !_MODULE_RENDERER_H_