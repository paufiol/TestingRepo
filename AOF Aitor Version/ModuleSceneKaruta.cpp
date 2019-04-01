#include "Globals.h"
#include "Application.h"
#include "ModuleSceneKaruta.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"

#include "SDL/include/SDL.h"

// Reference at https://youtu.be/6OlenbCC4WI?t=382

ModuleSceneKaruta::ModuleSceneKaruta()
{
	// ground
	background = {0, 0, 538, 240};


}

ModuleSceneKaruta::~ModuleSceneKaruta()
{}

// Load assets
bool ModuleSceneKaruta::Start()
{
	LOG("Loading background assets");
	bool ret = true;
	graphics = App->textures->Load("Karuta.png");

	// TODO 1: Enable (and properly disable) the player module
	App->player->Enable();
	return ret;
}

// Load assets
bool ModuleSceneKaruta::CleanUp()
{
	// TODO 5: Remove all memory leaks
	SDL_DestroyTexture(graphics);
	LOG("Unloading Karuta stage");

	return true;
}

// Update: draw background
update_status ModuleSceneKaruta::Update()
{
	

	App->render->Blit(graphics, 0, 0, &background, 0.75f);
	// TODO 2: make so pressing SPACE the KEN stage is loaded
	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1)
	{
		App->fade->FadeToBlack(  (Module*)App->scene_karuta, (Module*)App->scene_bar, 3.0f);
	}
	return UPDATE_CONTINUE;
}