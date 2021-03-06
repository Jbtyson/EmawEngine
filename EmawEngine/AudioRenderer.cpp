#include "stdafx.h"
#include <iostream>
#include <cstdlib>
#include <string>
#include <stddef.h>
#include "AudioRenderer.h"

using namespace std;

//Singleton instance
AudioRenderer* AudioRenderer::instance = NULL;

//Method for getting an instance
AudioRenderer* AudioRenderer::Instance(){
	if (!instance){
		instance = new AudioRenderer;
	}
	return instance;
}

//Method for destroying the instance and shutting down her system
//Needs to be called before the shutdown the game
void AudioRenderer::destroy(){
	if (instance){
		delete instance;
	}
}

//Initialization of the system
AudioRenderer::AudioRenderer(){
	FMOD_RESULT result;
	void *extradriverdata = 0;

	result = FMOD::System_Create(&system);

	checkProblem(result);

	result = system->init(CHANNELS_COUNT, FMOD_INIT_NORMAL, extradriverdata);

	checkProblem(result);

	result = system->set3DSettings(DOPPLER_SCALE, DISTANCE_FACTOR, ROLLOFF_SCALE);

	checkProblem(result);
}

//Shutting down the system
AudioRenderer::~AudioRenderer(){
	system->close();
	system->release();
}

//Method for playing music
//Stops the currently running music.
bool AudioRenderer::playMusic(Music *music){
	FMOD_RESULT result;

	bool playing;

	result = musicChannel->isPlaying(&playing);

	if (playing && checkResult(result)){
		stopMusic();
	}

	result = system->playSound(music->sound, 0, false, &musicChannel);

	if (!checkResult(result)){
		return false;
	}

	return updateSystem();
}

//Method for pause/unpause music
bool AudioRenderer::pauseMusic(){
	FMOD_RESULT result;
	bool paused;

	result = musicChannel->getPaused(&paused);

	if (!checkResult(result)){
		return false;
	}

	result = musicChannel->setPaused(!paused);

	if (!checkResult(result)){
		return false;
	}

	return updateSystem();
}

//Method for stopping music
bool AudioRenderer::stopMusic(){
	FMOD_RESULT result;

	result = musicChannel->stop();

	if (!checkResult(result)){
		return false;
	}

	return updateSystem();
}

//Method for playing SFX
//Default implementation
bool AudioRenderer::playSFX(SFX *sfx){
	FMOD_RESULT result;

	result = system->playSound(sfx->sound, 0, false, &SFXChannel);

	if (!checkResult(result)){
		return false;
	}

	return updateSystem();
}

//Method for loading music
Sound* AudioRenderer::load(string name, AudioManager* am){
	return am->load(name, system);
}

//Method for loading and playing music
void AudioRenderer::loadAndPlayMusic(string name, AudioManager* am){
	Music * m = (Music*)(am->loadLoop(name, system));
	playMusic(m);
}


//Method for mute/unmute music
bool AudioRenderer::muteMusic(){
	FMOD_RESULT result;
	bool muted;

	result = musicChannel->getMute(&muted);

	if (!checkResult(result)){
		return false;
	}

	result = musicChannel->setMute(!muted);

	if (!checkResult(result)){
		return false;
	}

	return updateSystem();
}

//Method for turning the volume of music up
bool AudioRenderer::musicVolumeUp(){
	return musicVolumeChangeBy(0.1f);
}

//Method for turning the volume of music down
bool AudioRenderer::musicVolumeDown(){
	return musicVolumeChangeBy(-0.1f);
}

//Method for changing the volume of music
bool AudioRenderer::musicVolumeChangeBy(float amount){
	FMOD_RESULT result;
	float volume;

	result = musicChannel->getVolume(&volume);

	if (!checkResult(result)){
		return false;
	}

	volume += amount;

	if (volume < MIN_VOLUME){
		volume = MIN_VOLUME;
	}
	else if (volume > MAX_VOLUME){
		volume = MAX_VOLUME;
	}

	result = musicChannel->setVolume(volume);

	if (!checkResult(result)){
		return false;
	}

	return updateSystem();
}

//Method for setting the volume of music to default value
bool AudioRenderer::musicVolumeReset(){
	FMOD_RESULT result;

	result = musicChannel->setVolume(DEFAULT_VOLUME);

	if (!checkResult(result)){
		return false;
	}

	return updateSystem();
}

//Method for updating the system
bool AudioRenderer::updateSystem(){
	FMOD_RESULT result;

	result = system->update();

	return checkResult(result);
}

//Method for turning the volume of SFX up
bool AudioRenderer::SFXVolumeUp(){
	return SFXVolumeChangeBy(0.1f);
}

//Method for turning the volume of SFX down
bool AudioRenderer::SFXVolumeDown(){
	return SFXVolumeChangeBy(-0.1f);
}

//Method for changing the volume of SFX
bool AudioRenderer::SFXVolumeChangeBy(float amount){
	FMOD_RESULT result;
	float volume;

	result = SFXChannel->getVolume(&volume);

	if (!checkResult(result)){
		return false;
	}

	volume += amount;

	if (volume < MIN_VOLUME){
		volume = MIN_VOLUME;
	}
	else if (volume > MAX_VOLUME){
		volume = MAX_VOLUME;
	}

	result = SFXChannel->setVolume(volume);

	if (!checkResult(result)){
		return false;
	}

	return updateSystem();
}

//Method for setting the volume of SFX to default value
bool AudioRenderer::SFXVolumeReset(){
	FMOD_RESULT result;

	result = SFXChannel->setVolume(DEFAULT_VOLUME);

	if (!checkResult(result)){
		return false;
	}

	return updateSystem();
}

//Method for loading and playing SFX
void AudioRenderer::loadAndPlaySFX(string name, AudioManager* am){
	SFX * s = (SFX*)load(name, am);
	playSFX(s);
}


//Method for mute/unmute SFX
bool AudioRenderer::muteSFX(){
	FMOD_RESULT result;
	bool muted;

	result = SFXChannel->getMute(&muted);

	if (!checkResult(result)){
		return false;
	}

	result = SFXChannel->setMute(!muted);

	if (!checkResult(result)){
		return false;
	}

	return updateSystem();
}

//Method for playing SFX on 3D Channel
FMOD::Channel* AudioRenderer::getNew3DChannel(){
	FMOD::Channel *channel = 0;

	return channel;
}

//Method for playing 3D SFX
void AudioRenderer::playTDSFX(TDSFX *tdsfx, FMOD::Channel *channel, Position* position){
	FMOD_RESULT result;

	FMOD_VECTOR vel = { 0.0f, 0.0f, 0.0f };
	system->playSound(tdsfx->sound, 0, true, &channel);
	result = channel->set3DAttributes(&(position->getVector()), &vel);
	channel->setPaused(false);

	updateSystem();
}


//Set sound system
bool AudioRenderer::setSoundSystem(AudioManager* am){
	return am->setSoundSystem(system);
}

//Method for loading 3D SFX
TDSFX * AudioRenderer::loadTDSFX(string filename, string name, Position* position){
	return (AudioManager::getInstance())->load3DLoop(filename, name, position, system);
}