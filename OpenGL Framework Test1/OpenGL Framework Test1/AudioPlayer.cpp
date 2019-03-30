#include "AudioPlayer.h"

std::unordered_map<std::string, AudioTrack*> AudioPlayer::tracksLoaded = std::unordered_map<std::string, AudioTrack*>();
bool AudioPlayer::listenerFlag = true;
FMOD_RESULT AudioPlayer::result;
FMOD::System* AudioPlayer::system = nullptr;
unsigned int AudioPlayer::version = 0;

bool AudioPlayer::init(int maxChannels, FMOD_INITFLAGS flags, void * extraDriverData)
{
	//Create system
	result = FMOD::System_Create(&system);
	if (errorCheck(result))
	{
		printf("Error while creating FMOD system");
		return false;
	}

	//Grab version
	system->getVersion(&version);

	//error check
	if (version < FMOD_VERSION)
	{
		printf("FMOD lib version %u doesn't match header version %u", version, (unsigned int)FMOD_VERSION);
		return false;
	}

	result = system->init(maxChannels, flags, extraDriverData);
	return true;
}

bool AudioPlayer::set3DSettings(float dopplerScale, float rollOffScale)
{
	result = system->set3DSettings(dopplerScale, DISTANCEFACTOR, rollOffScale);
	if (errorCheck(result))
	{
		printf("Error while setting the 3D settings");
		return false;
	}
	return true;
}

bool AudioPlayer::setMinMaxSettings(std::string fileName, float minDist, float maxDist)
{
	if (searchTrack(fileName) == nullptr)
	{
		printf("This AudioTrack isn't currently loaded");
		return false;
	}

	result = tracksLoaded[fileName]->sound->set3DMinMaxDistance(minDist * DISTANCEFACTOR, maxDist * DISTANCEFACTOR);
	if (errorCheck(result))
	{
		printf("Error while setting the min max settings for the audio");
		return false;
	}
	return true;
}

void AudioPlayer::setListenerPosition(FMOD_VECTOR& position, FMOD_VECTOR& velocity, FMOD_VECTOR& forward, FMOD_VECTOR& up)
{
	result = system->set3DListenerAttributes(0, &position, &velocity, &forward, &up);
	if (errorCheck(result))
	{
		printf("Error while setting listener attributes");
	}
}

bool AudioPlayer::loadAudio(AudioTrack & audio, std::string fileName)
{
	result = system->createSound(audio.fileName.c_str(), audio.dimension, 0, &audio.sound);
	if (errorCheck(result))
	{
		printf("Error while creaating sound at %s", audio.fileName.c_str());
		return false;
	}

	result = audio.sound->set3DMinMaxDistance(audio.minDist * DISTANCEFACTOR, audio.maxDist * DISTANCEFACTOR);
	if (errorCheck(result))
	{
		printf("Error while setting the min max distance at %s", audio.fileName.c_str());
		return false;
	}

	result = audio.sound->setMode(audio.doesLoop ? FMOD_LOOP_NORMAL : FMOD_LOOP_OFF);
	if (errorCheck(result))
	{
		printf("Error while setting the audio loop mode at %s", audio.fileName.c_str());
		return false;
	}

	tracksLoaded.insert(std::make_pair(fileName, &audio));

	return true;
}

bool AudioPlayer::unloadAudio(std::string fileName)
{
	if (searchTrack(fileName) == nullptr)
	{
		printf("This AudioTrack isn't currently loaded");
		return false;
	}

	result = tracksLoaded[fileName]->sound->release();
	if (errorCheck(result))
	{
		printf("Error while unloading the audio track at %s", tracksLoaded[fileName]->fileName.c_str());
		return false;
	}

	if (tracksLoaded[fileName] != nullptr) 
	{
		delete tracksLoaded[fileName];
		tracksLoaded[fileName] = nullptr;
	}
	tracksLoaded.erase(fileName);

	return true;
}

bool AudioPlayer::panAudio(std::string fileName, Degrees _panning, FMOD_VECTOR point)
{
	if (searchTrack(fileName) == nullptr)
	{
		printf("This AudioTrack isn't currently loaded");
		return false;
	}

	AudioTrack* track = searchTrack(fileName);
	track->panning += _panning;

	glm::mat4 rotationXMat = glm::rotate(glm::radians(0.f), glm::vec3(1.f, 0.f, 0.f));
	glm::mat4 rotationYMat = glm::rotate(glm::radians(_panning), glm::vec3(0.f, 1.f, 0.f));
	glm::mat4 rotationZMat = glm::rotate(glm::radians(0.f), glm::vec3(0.f, 0.f, 1.f));

	glm::mat4 rotationMat = rotationZMat * rotationYMat * rotationXMat;

	glm::vec3 temp = glm::vec3(track->position.x - point.x, track->position.y - point.y, track->position.z - point.z);
	glm::vec4 temp2 = rotationMat * glm::vec4(temp, 1.f);

	track->position = { temp2.x + point.x, temp2.y + point.y , temp2.z + point.z};
	
	return true;
}

bool AudioPlayer::setRolloff(std::string fileName, RollOffType _type)
{
	switch (_type) {
	case LINEAR:
		tracksLoaded[fileName]->channel->setMode(FMOD_3D_LINEARROLLOFF);
		break;
	case LOGARITHMIC:
		tracksLoaded[fileName]->channel->setMode(FMOD_3D_INVERSEROLLOFF);
		break;
	}

	return false;
}

bool AudioPlayer::setVolume(std::string fileName, float volume)
{
	if (searchTrack(fileName) == nullptr)
	{
		printf("This AudioTrack isn't currently loaded");
		return false;
	}

	result = tracksLoaded[fileName]->channel->setVolume(volume);
	if (errorCheck(result))
	{
		printf("Error changing the volume for audio track at %s", tracksLoaded[fileName]->fileName.c_str());
		return false;
	}
	
	return true;
}

bool AudioPlayer::prepareTrack(std::string fileName)
{
	if (searchTrack(fileName) == nullptr)
	{
		printf("This AudioTrack isn't currently loaded");
		return false;
	}

	AudioTrack* track = tracksLoaded[fileName];

	if (!track->prepared)
	{
		result = system->playSound(track->sound, 0, track->paused, &track->channel);
		if (errorCheck(result))
		{
			printf("Error playing the sound for audio track at %s", tracksLoaded[fileName]->fileName.c_str());
			return false;
		}

		result = track->channel->set3DAttributes(&track->position, &track->velocity);
		if (errorCheck(result))
		{
			printf("Error setting the 3D attributes for audio track at %s", tracksLoaded[fileName]->fileName.c_str());
			return false;
		}

		track->prepared = true;
	}

	return true;
}

bool AudioPlayer::prepareTrack(std::string original, std::string copy)
{
	if (searchTrack(original) == nullptr)
	{
		printf("This AudioTrack isn't currently loaded");
		return false;
	}

	AudioTrack* track = new AudioTrack(*tracksLoaded[original]);
	
	result = system->playSound(track->sound, 0, track->paused, &track->channel);
	if (errorCheck(result))
	{
		printf("Error copying the sound for audio track at %s", track->fileName.c_str());
		return false;
	}

	result = track->channel->set3DAttributes(&track->position, &track->velocity);
	if (errorCheck(result))
	{
		printf("Error setting the 3D attributes for audio Track at %s", track->fileName.c_str());
		return false;
	}

	tracksLoaded.insert(std::make_pair(copy, track));

	return true;
}

bool AudioPlayer::playTrack(std::string fileName)
{
	if (searchTrack(fileName) == nullptr)
	{
		printf("This AudioTrack isn't currently loaded");
		return false;
	}

	result = tracksLoaded[fileName]->channel->setPaused(false);
	tracksLoaded[fileName]->paused = false;

	return true;
}

void AudioPlayer::playTrack(AudioTrack* audio, float volume)
{
	result = system->createSound(audio->fileName.c_str(), audio->dimension, 0, &audio->sound);

	result = audio->sound->set3DMinMaxDistance(audio->minDist * DISTANCEFACTOR, audio->maxDist * DISTANCEFACTOR);

	result = audio->sound->setMode(false ? FMOD_LOOP_NORMAL : FMOD_LOOP_OFF);

	result = audio->channel->setVolume(volume);

	result = system->playSound(audio->sound, 0, false, &audio->channel);

	result = audio->channel->set3DAttributes(&audio->position, &audio->velocity);
	
	delete audio;
	audio = nullptr;
}

void AudioPlayer::removeTrack(std::string fileName)
{
	if (searchTrack(fileName) != nullptr)
	{
		tracksLoaded.erase(fileName);
	}
}

bool AudioPlayer::pauseTrack(std::string fileName)
{
	if (searchTrack(fileName) == nullptr)
	{
		printf("This AudioTrack isn't currently loaded");
		return false;
	}
	
	result = tracksLoaded[fileName]->channel->setPaused(true);
	if (errorCheck(result))
	{
		printf("Error unpausing the audio track at %s", tracksLoaded[fileName]->fileName.c_str());
		return false;
	}
	tracksLoaded[fileName]->paused = true;

	return true;
}

bool AudioPlayer::update(float deltaTime)
{
	for (auto pair : tracksLoaded)
	{
		AudioTrack* track = pair.second;

		result = track->channel->set3DAttributes(&track->position, &track->velocity);
	}

	system->update();

	return true;
}

bool AudioPlayer::close()
{
	result = system->close();
	if (errorCheck(result))
	{
		printf("Error while closing the system");
		return false;
	}

	result = system->release();
	if (errorCheck(result))
	{
		printf("Error while releasing the system");
		return false;
	}

	for (auto pair : tracksLoaded)
	{
		delete pair.second;
		pair.second = nullptr;
	}

	return true;
}

AudioTrack* AudioPlayer::searchTrack(std::string fileName)
{
	if (tracksLoaded.find(fileName) != tracksLoaded.end())
	{
		return tracksLoaded[fileName];
	}
	else 
	{
		return nullptr;
	}
}

bool AudioPlayer::errorCheck(FMOD_RESULT result)
{
	return (result != FMOD_OK);
}

FMOD_VECTOR convertVector(glm::vec3 vector)
{
	return { vector.x, vector.y, vector.z };
}

glm::vec3 convertVector(FMOD_VECTOR vector)
{
	return glm::vec3(vector.x, vector.y, vector.z);
}
