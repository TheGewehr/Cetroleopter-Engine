#include "ModuleTextureComponent.h"
#include "ModuleGameObject.h"
#include "Component.h"

TextureComponent::TextureComponent(ModuleGameObject* base) : Component(base, ComponentTypes::TEXTURE, "Mesh")
{
	
}

TextureComponent::~TextureComponent()
{
	
}

