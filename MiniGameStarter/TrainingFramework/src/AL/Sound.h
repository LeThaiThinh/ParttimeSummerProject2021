#pragma once
#include"SoundBuffer.h"
#include"SoundDevice.h"
#include"SoundSource.h"
#include "utilities.h"
#include<iostream>
class Sound
{
private:
	SoundDevice* m_soundDevice = SoundDevice::get();
	SoundSource m_soundSource;
	uint32_t m_song;
	std::string m_path = "";
public:
	Sound(const std::string& path);
	void PlaySound();
	void Play();
	void PlayLoopSound();
	void PlayLoop();
	void Stop();
};

