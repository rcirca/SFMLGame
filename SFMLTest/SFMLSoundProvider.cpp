#include "SFMLSoundProvider.h"

SFMLSoundProvider::SFMLSoundProvider() :
_currentSongName("")
{
	
}

SFMLSoundProvider::~SFMLSoundProvider()
{
}

bool SFMLSoundProvider::isSongPlaying()
{
	if (_currentSongName != "")
		return _soundFileCache.getSong(_currentSongName)->getStatus() == sf::Sound::Playing;

	return false;
}

bool SFMLSoundProvider::isSoundPlaying()
{
	for(auto i = 0; i < MAX_SOUND_CHANNELS; i++)
	{
		if (_currentSounds[i].getStatus() == sf::Sound::Playing)
			return true;
	}
	return false;
}

void SFMLSoundProvider::playSound(std::string fileName)
{
	int availableChannel = -1;
	for(auto i = 0; i < MAX_SOUND_CHANNELS; i++)
	{
		if(_currentSounds[i].getStatus() != sf::Sound::Playing)
		{
			availableChannel = i;
			break;
		}
	}

	if(availableChannel != -1)
	{
		try
		{
			_currentSounds[availableChannel] = _soundFileCache.getSound(fileName);
			_currentSounds[availableChannel].play();
		}
		catch(SoundNotFoundException& exception)
		{
			
		}
	}

}

void SFMLSoundProvider::playSong(std::string fileName, bool looping)
{
	sf::Music* currentSong;
	try
	{
		currentSong = _soundFileCache.getSong(fileName);
	}
	catch(SoundNotFoundException& exception)
	{
		return;
	}

	if(_currentSongName != "")
	{
		try
		{
			auto* priorSong = _soundFileCache.getSong(_currentSongName);
			if (priorSong->getStatus() != sf::Sound::Stopped)
				priorSong->stop();
		}
		catch(SoundNotFoundException& exception)
		{
			
		}
	}

	_currentSongName = fileName;
	currentSong->setLoop(looping);
	currentSong->play();
}

void SFMLSoundProvider::stopAllSounds()
{
	for(auto i = 0; i < MAX_SOUND_CHANNELS; i++)
	{
		auto* currentSong = _soundFileCache.getSong(_currentSongName);
		if (currentSong->getStatus() != sf::Sound::Stopped)
			currentSong->stop();
	}
}





