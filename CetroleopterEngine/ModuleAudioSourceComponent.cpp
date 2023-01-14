#include "ModuleAudioSourceComponent.h"
#include "ModuleAudio.h"
#include "ModuleGameObject.h"
#include "ModuleTransformComponent.h"

#include "mmgr/mmgr.h"

AudioSourceComponent::AudioSourceComponent(ModuleGameObject* base) : Component(base, ComponentTypes::AUDIOSOURCE, "AudioSource")
{
	float3 pos = base->GetTransformComponent()->GetPosition();
	sound = CreateSoundObj(base->id_, base->GetName().c_str(), pos.x, pos.y, pos.z);
}

AudioSourceComponent::~AudioSourceComponent()
{
}

bool AudioSourceComponent::Init()
{
	return true;
}

update_status AudioSourceComponent::Update()
{
	return UPDATE_CONTINUE;
}

bool AudioSourceComponent::CleanUp()
{
	return true;
}

bool AudioSourceComponent::SaveRequest(int positionInList)
{
	return true;
}

bool AudioSourceComponent::LoadRequest(int positionInList)
{
	return true;
}
