#ifndef _MODULE_TEXTURE_COMPONENT_H_
#define _MODULE_TEXTURE_COMPONENT_H_


#include "MathGeoLib.h"
#include "Application.h"
#include "Globals.h"
#include "ModuleGameObject.h"
#include "ModuleModelImport.h"

class ModuleGameObject;
class ModuleModelImport;

struct TextureData; //<-- Here yes

class TextureComponent : public Component
{
public:
	TextureComponent(ModuleGameObject* base);
	~TextureComponent();

	bool Init();
	update_status Update();
	bool CleanUp();

public:
	std::vector<TextureData*> textures;
	TextureData* objectTexture;

	const char* texturePath;
};


#endif // !_MODULE_TEXTURE_COMPONENT_H_

