//Class for rendering of sound effects
//Author: Ondrej Kuzela

#pragma once
#include "Music.h"
#include "SFX.h"
#include "TDSFX.h"
#include "fmod/fmod.hpp"
#include "AudioManager.h"
#include "Utils.h"
#include "Position.h"

class AudioRenderer {
private:
	AudioRenderer();

	//Singleton instance
	static AudioRenderer* instance;

	//FMOD System
	FMOD::System     *system;

	//FMOD channel for playing music
	FMOD::Channel    *musicChannel = 0;

	//FMOD channel for playing SFX
	FMOD::Channel    *SFXChannel = 0;
public:
	//Method for getting an instance
	static AudioRenderer* Instance();

	~AudioRenderer();

	//Method for playing music
	bool playMusic(Music *music);

	//Method for pause/unpause music
	bool pauseMusic();

	//Method for mute/unmute music
	bool muteMusic();

	//Method for stopping music
	bool stopMusic();

	//Method for loading and playing music
	void loadAndPlayMusic(string name, AudioManager* am);

	//Method for playing SFX
	bool playSFX(SFX *sfx);

	//Method for loading music
	Sound* load(string name, AudioManager* am);

	//Method for destroying the instance and shutting down her system
	static void destroy();

	//Method for turning the volume of music up
	bool musicVolumeUp();

	//Method for turning the volume of music down
	bool musicVolumeDown();

	//Method for changing the volume of music
	bool musicVolumeChangeBy(float amount);

	//Method for setting the volume of music to default value
	bool musicVolumeReset();

	//Method for updating the system
	bool updateSystem();

	//Method for loading and playing SFX
	void loadAndPlaySFX(string name, AudioManager* am);

	//Method for mute/unmute SFX
	bool muteSFX();

	//Method for turning the volume of SFX up
	bool SFXVolumeUp();

	//Method for turning the volume of SFX down
	bool SFXVolumeDown();

	//Method for changing the volume of SFX
	bool SFXVolumeChangeBy(float amount);

	//Method for setting the volume of SFX to default value
	bool SFXVolumeReset();

	//Method for getting new 3D Channel
	FMOD::Channel* AudioRenderer::getNew3DChannel();

	//Method for playing 3D SFX
	void playTDSFX(TDSFX *tdsfx, FMOD::Channel *channel, Position* position);

	//Method for loading 3D SFX
	TDSFX * loadTDSFX(string filename, string name, Position* position);

	//Set sound system
	bool setSoundSystem(AudioManager* am);
};