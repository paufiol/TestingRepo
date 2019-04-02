#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleSceneBar.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleAudio.h"

#include "SDL/include/SDL.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModuleSceneBar::ModuleSceneBar()
{
	

	// Background / sky
	background = { 0, 0, 538, 240 };


	// for moving the foreground
	foreground_pos = 0;
	forward = true;
}

ModuleSceneBar::~ModuleSceneBar()
{}

// Load assets
bool ModuleSceneBar::Start()
{
	LOG("Loading Bar scene");
	App->audio->PlayMusic("Splash_song.ogg", -1);
	graphics = App->textures->Load("Bar.png");

	// TODO 1: Enable (and properly disable) the player module
	App->player->Enable();
	
	return true;
}

// UnLoad assets
bool ModuleSceneBar::CleanUp()
{
	App->audio->StopMusic();
	SDL_DestroyTexture(graphics);
	LOG("Unloading Bar scene");

	return true;
}

// Update: draw background
update_status ModuleSceneBar::Update()
{
	

	// Draw everything --------------------------------------
	App->render->Blit(graphics, 0, 0, &background, 0.75f);
	
	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1)
	{
		App->fade->FadeToBlack((Module*)App->scene_bar, (Module*)App->scene_end,  2.0f);
	}
	return UPDATE_CONTINUE;
}