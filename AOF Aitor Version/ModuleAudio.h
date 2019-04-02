#pragma once
#include "Module.h"
#include "Globals.h"
#include "SDL_mixer/include/SDL_mixer.h"
#include "SDL/include/SDL.h"

#ifndef __ModuleAudio_H__
#define __ModuleAudio_H__

#define MAX_CHUNKS 50
#define DEFAULT_VOLUME 64

class ModuleAudio : public Module
{
public:

	ModuleAudio();
	~ModuleAudio();

	bool Init();
	update_status Update();
	bool CleanUp() ;
	Mix_Chunk * LoadChunk(const char* path);
	bool PlayMusic(const char* path, int loops);
	bool PlayChunk(Mix_Chunk * sound);
	void StopMusic();

public:
	Mix_Chunk * chunks[MAX_CHUNKS];
	Mix_Music * music; 

	Mix_Chunk* koukenFx;
};

#endif // __ModuleAudio_H__