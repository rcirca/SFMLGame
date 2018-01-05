#pragma once
#include "stdafx.h"
#include "IAudioProvider.h"

class ServiceLocator
{
public:
	static IAudioProvider* getAudio() { return _audioProvider; } const

	static void registerServiceLocator(IAudioProvider *audioProivder)
	{
		_audioProvider = audioProivder;
	}
private:
	static IAudioProvider* _audioProvider;
};