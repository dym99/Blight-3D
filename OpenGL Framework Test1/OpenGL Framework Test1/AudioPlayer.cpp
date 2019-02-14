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

bool AudioPlayer::loadAudio(AudioTrack & audio, std::string fileName)
{
	result = system->createSound(audio.fileName.c_str(), audio.dimension, 0, &audio.sound);
	if (errorCheck(result))
	{
		printf("Error while creaating sound at %s", audio.fileName);
		return false;
	}

	result = audio.sound->set3DMinMaxDistance(audio.minDist * DISTANCEFACTOR, audio.maxDist * DISTANCEFACTOR);
	if (errorCheck(result))
	{
		printf("Error while setting the min max distance at %s", audio.fileName);
		return false;
	}

	result = audio.sound->setMode(audio.doesLoop ? FMOD_LOOP_NORMAL : FMOD_LOOP_OFF);
	if (errorCheck(result))
	{
		printf("Error while setting the audio loop mode at %s", audio.fileName);
		return false;
	}

	tracksLoaded.insert(std::make_pair(fileName, &audio));

	AudioTrack* track = tracksLoaded[fileName];

	result = system->playSound(track->sound, 0, track->paused, &track->channel);
	if (errorCheck(result))
	{
		printf("Error playing the sound for audio track at %s", tracksLoaded[fileName]->fileName);
		return false;
	}

	result = track->channel->set3DAttributes(&track->position, &track->velocity);
	if (errorCheck(result))
	{
		printf("Error setting the 3D attributes for audio track at %s", tracksLoaded[fileName]->fileName);
		return false;
	}

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
		printf("Error while unloading the audio track at %s", tracksLoaded[fileName]->fileName);
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

bool AudioPlayer::panAudio(std::string fileName, Degrees panning)
{
	if (searchTrack(fileName) == nullptr)
	{
		printf("This AudioTrack isn't currently loaded");
		return false;
	}

	return true;
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
		printf("Error changing the volume for audio track at %s", tracksLoaded[fileName]->fileName);
	}
	
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
	if (errorCheck(result))
	{
		printf("Error unpausing the audio track at %s", tracksLoaded[fileName]->fileName);
		return false;
	}
	tracksLoaded[fileName]->paused = false;

	return true;
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
		printf("Error unpausing the audio track at %s", tracksLoaded[fileName]->fileName);
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
		if (errorCheck(result))
		{
			printf("Error updating the 3D attributes");
			return false;
		}
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
