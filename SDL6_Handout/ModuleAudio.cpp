#include "Globals.h"
#include "Application.h"
#include "ModuleAudio.h"
#include "SDL_mixer/include/SDL_mixer.h"
#include "SDL/include/SDL.h"

ModuleAudio::ModuleAudio() : Module()
{
	for (int i = 0; i < MAX_CHUNKS; i++) {
		chunks[i] = nullptr;
	}
}

// Destructor
ModuleAudio::~ModuleAudio()
{}

// Called before audio is available
bool ModuleAudio::Init()
{
	LOG("Init SDL Audio event system");
	bool ret = true;
	SDL_Init(0);

	if (Mix_Init(MIX_INIT_OGG) < 0)
	{
		LOG("Mix_Init could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}
	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1048) < 0)
	{
		LOG("Mix_Init could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

	Mix_VolumeMusic(DEFAULT_VOLUME);

	chunks[0] = LoadChunk("rtype/explosion.wav");
	return ret;
}

update_status ModuleAudio::Update() {
	update_status update = UPDATE_CONTINUE;

	



	return update;
}

bool ModuleAudio::CleanUp()
{	
	bool ret = true;
	while (!Mix_FadeOutMusic(3000) && Mix_PlayingMusic()) {
		// wait for any fades to complete
		SDL_Delay(100);
	}

	Mix_CloseAudio();
	Mix_Quit();

	return ret;
}

Mix_Chunk * ModuleAudio::LoadChunk(const char* path)
{
	Mix_Chunk* chunk = nullptr;
	chunk = Mix_LoadWAV(path);
	if (!path) {
		LOG("Mix_LoadWAV: %s\n", Mix_GetError());
			
	};
	return chunk;
}

bool ModuleAudio::PlayChunk(Mix_Chunk * sound)
{
	Mix_PlayChannel(-1, sound, 1);
	return true;
}

bool ModuleAudio::StopMusic()
{
	while (Mix_FadeOutMusic(2000) && Mix_PlayingMusic()) {
		SDL_Delay(100);
	}
	return true;
}

bool ModuleAudio::PlayMusic(const char* path, int loops)
{
	bool ret = true;

	//Mix_VolumeMusic(0);
	
	music = Mix_LoadMUS(path);

	if (!music) {
		LOG("Mix_LoadMUS: %s\n", Mix_GetError());
		ret = false; 
	};

	if (Mix_FadeInMusic(music, loops, 2000) < 0) {
		LOG("Mix_PlayMusic: %s\n", Mix_GetError());
		ret = false;
	}
	return ret;
}