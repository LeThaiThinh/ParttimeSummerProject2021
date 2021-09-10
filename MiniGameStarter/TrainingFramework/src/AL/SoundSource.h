#pragma once
#include <../../vcpkg/installed/x86-windows/include/AL/alext.h>
#include <../../vcpkg/installed/x86-windows/include/AL/al.h>
#include <../../vcpkg/packages/libsndfile_x86-windows/include/sndfile.h>
class SoundSource
{
public:
	SoundSource();
	~SoundSource();

	void Play(const ALuint buffer_to_play);

	void PlayLoop(const ALuint buffer_to_play);

	void Stop(const ALuint buffer_to_play);

private:
	bool isStopped;
	ALuint p_Source;
	float p_Pitch = 1.f;
	float p_Gain = 1.f;
	float p_Position[3] = { 0,0,0 };
	float p_Velocity[3] = { 0,0,0 };
	bool p_LoopSound = false;
	ALuint p_Buffer = 0;
};

