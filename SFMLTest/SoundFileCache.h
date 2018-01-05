#pragma once
#include "stdafx.h"

class SoundFileCache
{
public:
	SoundFileCache();
	~SoundFileCache();

	sf::Sound getSound(std::string fileName) const;
	sf::Music* getSong(std::string fileName) const;

private:
	static std::map<std::string, sf::SoundBuffer*> _sounds;
	static std::map<std::string, sf::Music*> _music;

	template <typename T>
	struct Deallocator
	{
		void operator()(const std::pair<std::string, T> &p)
		{
			delete p.second;
		}
	};
};


class SoundNotFoundException : public std::runtime_error
{
public:
	SoundNotFoundException(std::string const& msg):
	std::runtime_error(msg){}
};