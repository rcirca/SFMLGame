#pragma once
#include "stdafx.h"
#include "IAudioProvider.h"
#include "SoundFileCache.h"

class SFMLSoundProvider : public IAudioProvider
{
public:
	SFMLSoundProvider();
	~SFMLSoundProvider();
	void playSound(std::string fileName) override;
	void playSong(std::string fileName, bool looping = false) override;
	void stopAllSounds() override;
	bool isSoundPlaying() override;
	bool isSongPlaying() override;

private:
	static const int MAX_SOUND_CHANNELS = 5;

	SoundFileCache _soundFileCache;
	sf::Sound _currentSounds[MAX_SOUND_CHANNELS];
	std::string _currentSongName;
};