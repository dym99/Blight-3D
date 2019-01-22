#ifndef __AUDIOPLAYER_H__
#define __AUDIOPLAYER_H__

#include "FMOD/fmod.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

#define COMMONPATH "./Resources/Music/"
#define FILETYPE ".wav"
#define DISTANCEFACTOR 1.0f					//Units per meter, feet would be 3.28, centimeters would be 100


typedef float Degrees;

enum AudioType {
	SONG,
	EFFECT,

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
	}
	~AudioTrack()
	{

	}
	
	FMOD::Sound* sound;
	FMOD::Channel* channel;
	FMOD_MODE dimension;
	FMOD_MODE loop;
	AudioType type;
	std::string fileName;
	FMOD_VECTOR position;
	FMOD_VECTOR velocity;
	bool doesLoop;
	bool paused;
	float minDist;
	float maxDist;
};

class AudioPlayer abstract
{
public:
	//Initializes FMOD audio stuff
	static bool init(int maxChannels, FMOD_INITFLAGS flags, void* extraDriverData=NULL);
	static bool set3DSettings(float dopplerScale, float rollOffScale);

	//load audio files
	static bool loadAudio(AudioTrack &audio, std::string fileName);
	//unload audio files
	static bool unloadAudio(std::string fileName);
	//moves audio
	static bool panAudio(std::string fileName, Degrees panning);
	//sets volume
	static bool setVolume(std::string fileName, float volume);
	//plays track
	static bool playTrack(std::string fileName);
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
