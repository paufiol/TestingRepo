#include <math.h>
#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModulePlayer.h"

#include "SDL/include/SDL_timer.h"

ModuleParticles::ModuleParticles()
{
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
		active[i] = nullptr;
}

ModuleParticles::~ModuleParticles()
{}

// Load assets
bool ModuleParticles::Start()
{
	LOG("Loading particles");
	graphics = App->textures->Load("ryo.png");

	// Explosion particle //LAS COORDENADAS SE TIENEN QUE CAMBIAR
	//kouken.anim.PushBack({ 632, 348, 57, 108 });
	kouken.anim.PushBack({ 598, 879, 54, 106 });
	kouken.anim.PushBack({ 652, 883, 30, 102 });
	
	kouken.anim.PushBack({ 736, 905, 72, 47 });
	kouken.anim.PushBack({ 682, 913, 54, 39 });
	
	
	

	kouken.anim.loop = true;
	kouken.anim.speed = 0.1f;
	kouken.speed.x = 5;
	
	return true;
}

// Unload assets
bool ModuleParticles::CleanUp()
{
	LOG("Unloading particles");
	App->textures->Unload(graphics);

	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if(active[i] != nullptr)
		{
			delete active[i];
			active[i] = nullptr;
		}
	}

	return true;
}

// Update: draw background
update_status ModuleParticles::Update()
{
	App->audio->koukenFx = App->audio->LoadChunk("kouken.ogg");
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Particle* p = active[i];

		if(p == nullptr)
			continue;

		if(p->Update() == false)
		{
			delete p;
			active[i] = nullptr;
		}
		else if(SDL_GetTicks() >= p->born)
		{
		
			App->render->Blit(graphics, p->position.x + 50, p->position.y - 100, &(p->anim.GetCurrentFrame()));
			
		/*	SDL_Rect prueba = {App->player->position.x,App->player->position.y,300,50 };
			SDL_SetRenderDrawColor(App->render->renderer, 255, 0, 0, 0);
			SDL_RenderDrawRect(App->render->renderer, &prueba);
			SDL_SetRenderDrawColor(App->render->renderer, 0, 0, 0, 0);*/
			if(p->fx_played == false)
			{
				p->fx_played = true;
				// Play particle fx here //AQUI SONIDO HADDOKEN
				
				App->audio->PlayChunk(App->audio->koukenFx);
			}
		}
	}

	return UPDATE_CONTINUE;
}

void ModuleParticles::AddParticle(const Particle& particle, int x, int y, Uint32 delay)
{
	Particle* p = new Particle(particle);
	p->born = SDL_GetTicks() + delay;
	p->position.x = App->player->position.x;
	p->position.y = App->player->position.y;
	active[last_particle++] = p;
}

// -------------------------------------------------------------
// -------------------------------------------------------------

Particle::Particle()
{
	position.SetToZero();
	speed.SetToZero();
}

Particle::Particle(const Particle& p) : 
anim(p.anim), position(p.position), speed(p.speed),
fx(p.fx), born(p.born), life(p.life)
{}

bool Particle::Update()
{
	bool ret = true;

	if(life > 0)
	{
		if((SDL_GetTicks() - born) > life)
			ret = false;
	}
	else
		if(anim.Finished())
			ret = false;

	position.x += speed.x;
	position.y += speed.y;

	return ret;
}