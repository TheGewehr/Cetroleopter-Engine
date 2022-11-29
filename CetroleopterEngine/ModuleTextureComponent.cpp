#include "ModuleTextureComponent.h"
#include "ModuleGameObject.h"
#include "Component.h"

TextureComponent::TextureComponent(ModuleGameObject* base) : Component(base, ComponentTypes::TEXTURE, "Mesh")
{
	
}

TextureComponent::~TextureComponent()
{
	
}

bool TextureComponent::Init()
{


	return true;
}

update_status TextureComponent::Update()
{


	return UPDATE_CONTINUE;
}

bool TextureComponent::CleanUp()
{


	return true;
}