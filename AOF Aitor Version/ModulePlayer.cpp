#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModulePlayer::ModulePlayer()
{
	position.x = 100;
	position.y = 220;

	// idle animation (arcade sprite sheet)
	idle.PushBack({0, 8, 66, 108});
	idle.PushBack({66, 8, 67 , 108});
	idle.PushBack({133, 8, 69, 108 });
	idle.speed = 0.1f;

	// walk forward animation (arcade sprite sheet)
	//forward.frames.PushBack({9, 136, 53, 83});
	forward.PushBack({ 632, 348, 57, 108 });
	forward.PushBack({ 689, 348, 58, 108 });
	forward.PushBack({ 747, 348, 69, 108 });
	forward.PushBack({ 816, 348, 58, 108 });
	forward.PushBack({ 874, 348, 67, 108 });
	forward.speed = 0.15f;

	jump.PushBack({ 0,  456, 60, 130 });
	jump.PushBack({ 60, 456, 66, 130 });
	jump.PushBack({ 126, 456, 62, 130 });
	jump.PushBack({ 188, 456, 57 , 130 });
	jump.PushBack({ 245, 456, 53, 130 });
	jump.PushBack({ 0, 456, 56, 130 });
	jump.PushBack({ 299, 456, 56, 130 });
	jump.speed = 0.1f;

	punch.PushBack({ 485, 348,  58, 108});
	punch.PushBack({ 543, 348,  89, 108});
	punch.speed = 0.2f;   

	//AQUI
	// TODO 4: Make ryu walk backwards with the correct animations
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player textures");
	bool ret = true;
	graphics = App->textures->Load("ryo.png"); // arcade version
	return ret;
}

// Update: draw background
update_status ModulePlayer::Update()
{
	Animation* current_animation = &idle;

	int speed = 1;
	 
	if(!jumplock && !punchlock)
	{
		if (App->input->keyboard[SDL_SCANCODE_D] == 1)
		{
			current_animation = &forward;
			position.x += speed;
		}

		if (App->input->keyboard[SDL_SCANCODE_A] == 1)
		{
			current_animation = &forward;
			position.x -= speed;
		}

		if (App->input->keyboard[SDL_SCANCODE_W] == 1) {
			//current_animation = &jump;
			jumplock = true;
		}
		
		if (App->input->keyboard[SDL_SCANCODE_Q] == 1) {
			current_animation = &punch;
			punchlock = true; 
		}

		if (App->input->keyboard[SDL_SCANCODE_1] == KEY_STATE::KEY_DOWN) {
			App->particles->AddParticle(App->particles->kouken, position.x, position.y + 50, 0);
			//App->audio->PlayChunk(App->audio->chunks[0]);
		}
	}
	
	if (jumplock)
	{
		current_animation = &jump;
		if (current_animation->current_frame < 3) { position.y -= speed; }
		else { position.y += speed; }
		if ( ((current_animation->current_frame)+0.2f) >= current_animation->last_frame ) {
			jumplock = false;
		}
	}

	if (punchlock)
	{
		current_animation = &punch;
		
		if (((current_animation->current_frame) + 0.2f) >= current_animation->last_frame) {
			punchlock = false;
		}
	}

	// Draw everything --------------------------------------
	SDL_Rect r = current_animation->GetCurrentFrame();

	App->render->Blit(graphics, position.x, position.y - r.h, &r);
	
	return UPDATE_CONTINUE;
}