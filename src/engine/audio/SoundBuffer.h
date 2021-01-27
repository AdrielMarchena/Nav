#pragma once
#include <AL\al.h>
#include <vector>
class SoundBuffer
{
public:
	static SoundBuffer* get();

	ALuint addSoundEffect(const char* filename);

private:
	SoundBuffer();
	~SoundBuffer();

};

