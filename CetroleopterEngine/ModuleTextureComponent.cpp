#include "ModuleTextureComponent.h"
#include "ModuleGameObject.h"
#include "Component.h"

TextureComponent::TextureComponent(ModuleGameObject* base) : Component(base, ComponentTypes::TEXTURE, "Texture")
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

bool TextureComponent::SaveComponent()
{
	json_object_dotset_string(json_object(App->save_load->sceneFile), "Scene01.GameObjectsList.ID.TextureComponent.Path", texturePath);

	return false;
}

bool TextureComponent::LoadComponent()
{
	return false;
}
