#pragma once
#include <../../vcpkg/installed/x86-windows/include/AL/alext.h>
#include <../../vcpkg/installed/x86-windows/include/AL/al.h>
#include <../../vcpkg/packages/libsndfile_x86-windows/include/sndfile.h>
#include <vector>
class SoundBuffer
{
public:
	static SoundBuffer* get();

	ALuint addSoundEffect(const char* filename);
	bool removeSoundEffect(const ALuint& buffer);

private:
	SoundBuffer();
	~SoundBuffer();

	std::vector<ALuint> p_SoundEffectBuffers;
};

