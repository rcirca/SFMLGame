#include "SoundFileCache.h"

SoundFileCache::SoundFileCache()
{
	
}

SoundFileCache::~SoundFileCache()
{
	std::for_each(_sounds.begin(), _sounds.end(), Deallocator<sf::SoundBuffer*>());
	std::for_each(_music.begin(), _music.end(), Deallocator<sf::Music*>());
}

sf::Music* SoundFileCache::getSong(std::string fileName) const
{
	auto iterator = _music.find(fileName);
	if (iterator == _music.end())
	{
		auto song = new sf::Music();
		if(!song->openFromFile(fileName))
		{
			delete song;
			throw SoundNotFoundException(fileName + " was not found in call to SoundFileCache::getSong");
		}

		std::map<std::string, sf::Music *>::iterator res = _music.insert(std::pair<std::string, sf::Music*>(fileName, song)).first;
		return res->second;
	}

	return iterator->second;
}

sf::Sound SoundFileCache::getSound(std::string fileName) const
{
	auto iterator = _sounds.find(fileName);
	if (iterator == _sounds.end())
	{
		auto soundBuffer = new sf::SoundBuffer();
		if (!soundBuffer->loadFromFile(fileName))
		{
			delete soundBuffer;
			throw SoundNotFoundException(fileName + " was not found in call to SoundFileCache::getSound");
		}

		std::map<std::string, sf::SoundBuffer *>::iterator res = 
			_sounds.insert(std::pair<std::string, sf::SoundBuffer*>(fileName, soundBuffer)).first;

		sf::Sound sound;
		sound.setBuffer(*soundBuffer);
		return sound;
	}

	sf::Sound sound;
	sound.setBuffer(*iterator->second);
	return sound;
}


std::map<std::string, sf::SoundBuffer*> SoundFileCache::_sounds;
std::map<std::string, sf::Music*> SoundFileCache::_music;
