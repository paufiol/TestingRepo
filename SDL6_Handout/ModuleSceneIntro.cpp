#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleSceneIntro.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleSceneSpace.h"
#include "ModuleAudio.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModuleSceneIntro::ModuleSceneIntro()
{}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading intro scene");
	//this->Enable();
	App->audio->PlayMusic("rtype/intro.ogg", -1);
	intro = App->textures->Load("rtype/intro.png");

	App->player->Disable();

	return true;
}

// UnLoad assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading intro scene");


	App->textures->Unload(intro);
	App->player->Disable();

	return true;
}

// Update: draw background
update_status ModuleSceneIntro::Update()
{
	// Move camera forward -----------------------------
	int scroll_speed = 0;

	//App->player->position.x += 1;
	App->render->camera.x = 0;
	App->render->camera.y = -20;

	// Draw everything --------------------------------------
	App->render->Blit(intro, 0, 0, NULL);

	//Switch scenes --------------------------------------
	if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_DOWN) {
		App->fade->FadeToBlack(App->scene_intro, App->scene_space, 1.0f);
	}

	return UPDATE_CONTINUE;
}