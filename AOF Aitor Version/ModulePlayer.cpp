#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleCollision.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModulePlayer::ModulePlayer()
{
	position.x = 100;
	position.y = 112;

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

	koukenR.PushBack({ 176, 873, 66, 112 });
	koukenR.PushBack({ 242, 873, 88, 112 });
	koukenR.PushBack({ 330, 884, 85, 96 });
	koukenR.PushBack({ 415, 888, 81, 97 });
	koukenR.PushBack({ 496, 877, 102, 108 });
	koukenR.speed = 0.2f;


	//AQUI haced que de patadas
	
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player textures");
	bool ret = true;
	graphics = App->textures->Load("ryo.png"); // arcade version
	player = App->collision->AddCollider({ position.x, position.y-108, 57, 108 }, COLLIDER_PLAYER, this);
	return ret;
}

// Update: draw background
update_status ModulePlayer::Update()
{
	Animation* current_animation = &idle;

	int speed = 1;
	 
	if(!jumplock && !punchlock && !koukenlock)
	{
		if (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_DOWN)
		{
			current_animation = &forward;
			position.x += speed;
		}

		if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_DOWN)
		{
			current_animation = &forward;
			position.x -= speed;
		}

		if (App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_DOWN) {
			//current_animation = &jump;
			jumplock = true;
		}
		
		if (App->input->keyboard[SDL_SCANCODE_Q] == KEY_STATE::KEY_DOWN) {
			current_animation = &punch;
			punchlock = true; 
		}

		if (App->input->keyboard[SDL_SCANCODE_F] == KEY_STATE::KEY_DOWN) {
			current_animation = &koukenR;
			App->particles->AddParticle(App->particles->kouken, position.x, position.y, COLLIDER_PLAYER_SHOT);

			
			koukenlock = true;
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
	if (koukenlock)
	{
		current_animation = &koukenR;

		if (((current_animation->current_frame) + 0.2f) >= current_animation->last_frame) {
			koukenlock = false;
		}
	}

	// Draw everything --------------------------------------
	SDL_Rect r = current_animation->GetCurrentFrame();

	player->SetPos(position.x, position.y);

	App->render->Blit(graphics, position.x, position.y, &r);
	
	return UPDATE_CONTINUE;
}