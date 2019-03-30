#ifndef __AUDIOPLAYER_H__
#define __AUDIOPLAYER_H__

/////////////////////////////////////////////////////////////////////////////////////////////
//*Nicholas Juniper - 100659791 - 1/22/2019
//*Everything in this file was written by me
//*
//*
//*
/////////////////////////////////////////////////////////////////////////////////////////////
#include "include/FMOD/fmod.hpp"
#include "include/glm/common.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

#define GLM_ENABLE_EXPERIMENTAL
#include "include/glm/gtx/transform.hpp"

#define COMMONPATH "./Resources/Music/"
#define FILETYPE ".wav"
#define DISTANCEFACTOR 1.0f					//Units per meter, feet would be 3.28, centimeters would be 100


typedef float Degrees;

enum AudioType {
	SONG,
	EFFECT,

};

enum RollOffType {
	LINEAR, 
	LOGARITHMIC,
};

struct AudioTrack {
	AudioTrack() 
	{
		sound = nullptr;
		channel = nullptr;
		fileName = COMMONPATH + std::string("test") + FILETYPE;
		dimension = FMOD_3D;

		type = AudioType::SONG;
		doesLoop = false;
		paused = true;
		minDist = 0.f;
		maxDist = 100.f;

		position = { 0.f, 0.f, 0.f };
		velocity = { 0.f, 0.f, 0.f };
		panning = glm::radians(0.f);

		rollType = RollOffType::LOGARITHMIC;
	}

	AudioTrack(std::string _fileName, FMOD_MODE _dimension, AudioType _type, FMOD_VECTOR _position, FMOD_VECTOR _velocity, bool _doesLoop, float _minDist, float _maxDist)
	{
		sound = nullptr;
		channel = nullptr;
		fileName = COMMONPATH + _fileName + FILETYPE;
		dimension = _dimension;

		type = _type;
		doesLoop = _doesLoop;
		paused = true;
		minDist = _minDist;
		maxDist = _maxDist;

		position = _position;
		velocity = _velocity;
		panning = glm::radians(0.f);

		rollType = RollOffType::LOGARITHMIC;
	}
	
	FMOD::Sound* sound;
	FMOD::Channel* channel;
	FMOD_MODE dimension;
	FMOD_MODE loop;
	AudioType type;
	std::string fileName;
	FMOD_VECTOR position;
	FMOD_VECTOR velocity;
	Degrees panning;
	bool doesLoop;
	bool paused;
	bool prepared = false;
	float minDist;
	float maxDist;
	int iteration = 0;

	RollOffType rollType;
};

class AudioPlayer abstract
{
public:
	//Initializes FMOD audio stuff
	static bool init(int maxChannels, FMOD_INITFLAGS flags, void* extraDriverData=NULL);
	static bool set3DSettings(float dopplerScale, float rollOffScale);
	static bool setMinMaxSettings(std::string fileName, float minDist, float maxDist);
	static void setListenerPosition(FMOD_VECTOR& position, FMOD_VECTOR& velocity, FMOD_VECTOR& forward, FMOD_VECTOR& up);


	//load audio files
	static bool loadAudio(AudioTrack &audio, std::string fileName);
	//unload audio files
	static bool unloadAudio(std::string fileName);
	//moves audio
	static bool panAudio(std::string fileName, Degrees _panning, FMOD_VECTOR point);
	//Set rolloff 
	static bool setRolloff(std::string fileName, RollOffType _type);
	//sets volume
	static bool setVolume(std::string fileName, float volume);
	//Prepares track to play
	static bool prepareTrack(std::string fileName);
	//Prepares track to play on a new channel, accessed with a new name
	static bool prepareTrack(std::string original, std::string copied);
	//plays track
	static bool playTrack(std::string fileName);
	static void playTrack(AudioTrack* audio, float volume=1.f);
	
	static void removeTrack(std::string fileName);

	//Pauses track
	static bool pauseTrack(std::string fileName);

	static bool update(float deltaTime);

	//closes the audio player
	static bool close();
	//Helpers
	//Returns a track based on the given filename
	//If the track isn't loaded, it will return nullptr
	static AudioTrack* searchTrack(std::string fileName);
private:
	static bool errorCheck(FMOD_RESULT result);
	static std::unordered_map<std::string, AudioTrack*> tracksLoaded;
	//if the listener is listening
	static bool listenerFlag;
	//The fmod system
	static FMOD::System *system;
	//Used to hold results
	static FMOD_RESULT result;
	//version of FMOD
	static unsigned int version;

};


#endif
