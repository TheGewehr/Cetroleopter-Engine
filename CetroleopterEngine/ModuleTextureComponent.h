#ifndef _MODULE_TEXTURE_COMPONENT_H_
#define _MODULE_TEXTURE_COMPONENT_H_


#include "MathGeoLib.h"
#include "Application.h"
#include "Globals.h"
#include "ModuleGameObject.h"

class GameObject;
class ModuleModelImport;

class TextureComponent : public Component
{
public:
	TextureComponent();
	~TextureComponent();

	bool Init();
	update_status Update();
	bool CleanUp();

public:

};


#endif // !_MODULE_TEXTURE_COMPONENT_H_

