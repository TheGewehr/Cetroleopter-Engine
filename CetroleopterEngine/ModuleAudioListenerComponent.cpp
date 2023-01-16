#include "ModuleAudioListenerComponent.h"
#include "ModuleAudio.h"
#include "ModuleGameObject.h"
#include "ModuleTransformComponent.h"
#include "ModuleSceneIntro.h"
#include "ModuleCameraComponent.h"
#include <AK/SoundEngine/Common/AkSoundEngine.h>

#include "mmgr/mmgr.h"

AudioListenerComponent::AudioListenerComponent(ModuleGameObject* base) : Component(base, ComponentTypes::AUDIOLISTENER, "AudioListener")
{
	//float3 pos = base->GetTransformComponent()->GetPosition();
	//listener = CreateSoundObj(base->id_, base->GetName().c_str(), pos.x, pos.y, pos.z);
}

AudioListenerComponent::~AudioListenerComponent()
{
}

bool AudioListenerComponent::Init()
{
	//listener->PlayMusic("Assets/VISTIMA.mp3");
	return true;
}

update_status AudioListenerComponent::Update()
{
	//listener->SetPosition();


	/*listener->SetPosition(App->camera->mainCamera->frustum.pos.x, App->camera->mainCamera->frustum.pos.y, App->camera->mainCamera->frustum.pos.z,
						  App->camera->mainCamera->frustum.front.x, App->camera->mainCamera->frustum.front.y, App->camera->mainCamera->frustum.front.z,
						  App->camera->mainCamera->frustum.up.x, App->camera->mainCamera->frustum.up.y, App->camera->mainCamera->frustum.up.z);*/

	//Si no funciona con el frustum usar esta
	//listener->SetPosition(App->camera->mainCamera->Position.x, App->camera->mainCamera->Position.y, App->camera->mainCamera->Position.z,
	//						App->camera->mainCamera->frustum.front.x, App->camera->mainCamera->frustum.front.y, App->camera->mainCamera->frustum.front.z,
	//						App->camera->mainCamera->frustum.up.x, App->camera->mainCamera->frustum.up.y, App->camera->mainCamera->frustum.up.z);

	/*AKRESULT eResult = AK::SoundEngine::SetRTPCValue("Volume", 100, listener->GetID());
	if (eResult != AK_Success)
	{
		assert(!"Error changing audio volume!");
	}*/

	/*App->audio->SetVolume("Volume", App->audio->volume);
	App->audio->muted = false;*/

	return UPDATE_CONTINUE;
}

bool AudioListenerComponent::CleanUp()
{
	return true;
}

bool AudioListenerComponent::SaveRequest(int positionInList)
{
	return true;
}

bool AudioListenerComponent::LoadRequest(int positionInList)
{
	return true;
}
