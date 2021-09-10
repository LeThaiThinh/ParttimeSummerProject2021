#pragma once
#include <../../vcpkg/installed/x86-windows/include/AL/alext.h>
#include <../../vcpkg/installed/x86-windows/include/AL/al.h>
#include <../../vcpkg/packages/libsndfile_x86-windows/include/sndfile.h>
class SoundDevice
{
public:
	static SoundDevice* get();

private:
	SoundDevice();
	~SoundDevice();

	ALCdevice* p_ALCDevice;
	ALCcontext* p_ALCContext;

};

