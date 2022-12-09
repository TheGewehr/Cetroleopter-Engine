#ifndef _MODULE_RENDERER_H_
#define _MODULE_RENDERER_H_

#include "Module.h"
#include "Globals.h"
#include "glmath.h"
#include "Light.h"
#include <MathGeoLib.h>

#define GLVertexDD(idx) {float3& v = vertices[*idx - 1]; glVertex3f(v.x, v.y, v.z);}
#define MAX_LIGHTS 150

class ModuleRenderer3D : public Module
{
public:
	ModuleRenderer3D(bool start_enabled = true);
	~ModuleRenderer3D();

	bool Init();
	bool Start();
	update_status PreUpdate(float dt);
	update_status Update(float dt);
	update_status PostUpdate(float dt);
	bool CleanUp();

	void OnResize(int width, int height);

	void SetVsync(bool value);

	void RenderGameObjects(ModuleGameObject gameObject, float3 position);

public:

	Light lights[MAX_LIGHTS];
	SDL_GLContext context = NULL;
	mat3x3 NormalMatrix;
	mat4x4 ModelMatrix, ViewMatrix, ProjectionMatrix;
	bool wireframeMode = false;
	bool faceCullingMode = false;
	bool texturesOFF = false;
	bool disableLights = false;
	bool disableAO = false;
	bool vsyncEnabled = VSYNC;
	//bool showConsole = false;

	uint checkerTextureID;
	bool checkerTextureON;

	float vertices[9] = {
	-0.5f, -0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f,
	 0.0f,  0.5f, 0.0f
	};

	unsigned int VBO;

	const char* vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0";

	const char* fragmentShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0";


	vec4 FragColor;

	unsigned int vertexShader;
	unsigned int fragmentShader;
	unsigned int shaderProgram;

	unsigned int VAO;

};

#endif // !_MODULE_RENDERER_H_