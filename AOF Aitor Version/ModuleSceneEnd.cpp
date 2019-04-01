#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleSceneSplash.h"
#include "ModuleSceneEnd.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"

#include "SDL/include/SDL.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModuleSceneEnd::ModuleSceneEnd()
{


	// Background / sky
	background.x = 0;
	background.y = 0;
	background.w = 320;
	background.h = 240;
}

ModuleSceneEnd::~ModuleSceneEnd()
{}

// Load assets
bool ModuleSceneEnd::Start()
{
	LOG("Loading End scene");

	graphics = App->textures->Load("EndScreen.png");
	App->player->Disable();

	return true;
}

// UnLoad assets
bool ModuleSceneEnd::CleanUp()
{
	SDL_DestroyTexture(graphics);
	LOG("Unloading Splash scene");
	
	return true;
}

// Update: draw background
update_status ModuleSceneEnd::Update()
{
	// Draw everything --------------------------------------
	App->render->Blit(graphics, 0, 0, &background, 0.75f);
	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1)
	{
		App->fade->FadeToBlack((Module*)App->scene_end, (Module*)App->scene_splash, 1.0f);
	}
	return UPDATE_CONTINUE;
}