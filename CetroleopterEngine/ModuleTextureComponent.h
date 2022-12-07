#ifndef _MODULE_TEXTURE_COMPONENT_H_
#define _MODULE_TEXTURE_COMPONENT_H_


#include "MathGeoLib.h"
#include "Application.h"
#include "Globals.h"
//#include "ModuleGameObject.h"
#include "ModuleModelImport.h"
#include "Component.h"

class ModuleGameObject;
//class ModuleModelImport;

//struct TextureData; 

class TextureComponent : public Component
{
public:
	TextureComponent(ModuleGameObject* base);
	~TextureComponent();

	bool Init();
	update_status Update();
	bool CleanUp();

	bool SaveComponent();
	bool LoadComponent();

public:
	std::vector<TextureData*> textures;
	TextureData* objectTexture;

	const char* texturePath;
};


#endif // !_MODULE_TEXTURE_COMPONENT_H_

