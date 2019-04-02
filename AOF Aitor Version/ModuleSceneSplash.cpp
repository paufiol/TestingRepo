#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleSceneSplash.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "Application.h"
#include "ModuleAudio.h"
#include "ModuleAudio.h"
#include "SDL/include/SDL.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModuleSceneSplash::ModuleSceneSplash()
{
	// Background / sky
	background.x = 15;
	background.y = 0;
	background.w = 320;
	background.h = 240;
}

ModuleSceneSplash::~ModuleSceneSplash()
{}

// Load assets
bool ModuleSceneSplash::Start()
{
	LOG("Loading Splash scene");
	App->audio->PlayMusic("Splash_song.ogg", -1);
	graphics = App->textures->Load("Splash.png");

	return true;
}

// UnLoad assets
bool ModuleSceneSplash::CleanUp()
{
	SDL_DestroyTexture(graphics);
	App->audio->StopMusic();
	LOG("Unloading Splash scene");

	return true;
}

// Update: draw background
update_status ModuleSceneSplash::Update()
{
	// Draw everything --------------------------------------
	App->render->Blit(graphics, 0, 0, &background, 0.75f); 

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1)
	{

		App->fade->FadeToBlack((Module*)App->scene_splash, (Module*)App->scene_karuta, 2.0f);

	}
	return UPDATE_CONTINUE;
}