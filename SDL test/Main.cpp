#include <iostream>
#include <stdio.h>
#include <windows.h>
#include "SDL/include/SDL.h"
#include "SDL/include/SDL_image.h"
#include "SDL_mixer/include/SDL_mixer.h"

#pragma comment (lib, "SDL/Lib/SDL2main.lib")
#pragma comment (lib, "SDL/Lib/SDL2.lib")
#pragma comment (lib, "SDL/Lib/SDL2_image.lib")
#pragma comment (lib, "SDL_mixer/lib/SDL2_mixer.lib")

using namespace std;

const int SCREEN_WIDTH = 960;
const int SCREEN_HEIGHT = 640;

//#define LOG(txt) OutputDebugString(txt)

SDL_Texture* Loader(const char* file, SDL_Renderer* renderer) { //Esta cosa se dedica a preparar texturas
	SDL_Surface* LoadSurf = NULL;
	SDL_Texture* texture = NULL;

	LoadSurf = IMG_Load(file); 
	if (LoadSurf == NULL) {
		cout << IMG_GetError() << endl;
		return NULL;
	}

	texture = SDL_CreateTextureFromSurface(renderer, LoadSurf);
	SDL_FreeSurface(LoadSurf);
	return texture;
}

bool collide(SDL_Rect &objA, SDL_Rect &objB) {
	bool collide = false;
	if (abs((objA.x + objA.w) - objB.x) < 5) {
		
		for (int j = 0; j < objB.h; j++) {
		
			for (int i = 0; i < objA.h; i++) {
			
				if ((objA.y + i) == (objB.y + j)) {
					collide = true;
				}
			}
		}
	}
	return collide;
}

int main(int argc, char* argv[])
{
	//Init all
	SDL_Init(SDL_INIT_VIDEO);
	IMG_Init(IMG_INIT_PNG);
	Mix_Init(MIX_INIT_OGG);


	//Audio
	Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1048);

	Mix_Music* music = NULL;
	Mix_Chunk* guns = NULL; 
	Mix_Chunk* boom = NULL;

	music = Mix_LoadMUS("sound/ripandtear.ogg");
	if (!music) {
		//LOG("Mix_LoadMUS(\"music.mp3\"): %s\n", Mix_GetError());
		// this might be a critical error...
		
	}
	guns = Mix_LoadWAV("sound/laser.ogg");
	if (!guns) {
		//LOG("Mix_LoadMUS(\"music.mp3\"): %s\n", Mix_GetError());
		// this might be a critical error...
	}
	boom = Mix_LoadWAV("sound/boom2.ogg");
	if (!boom) {
		//printf("Mix_LoadMUS(\"music.mp3\"): %s\n", Mix_GetError());
		const char* a = Mix_GetError();
		// this might be a critical error...
		return 8;
	}


	Mix_VolumeMusic(32);

	Mix_VolumeChunk(guns, 64);


	const Uint8 *keystate = SDL_GetKeyboardState(NULL);

	SDL_Renderer* renderer = NULL;
	

	SDL_Window* window = NULL;
	window = SDL_CreateWindow
	(
		"NotABox",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		SDL_WINDOW_SHOWN
	);

	
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);

	//Create and load textures
	SDL_Texture* bg = NULL;
	SDL_Texture* ship = NULL;
	SDL_Texture* projectile = NULL;
	SDL_Texture* projectile2 = NULL;
	SDL_Texture* enemy = NULL; 

	bg = Loader("img/bg2.png", renderer);
	ship = Loader("img/nave3.png", renderer);
	projectile = Loader("img/projectile1.png", renderer);
	projectile2 = Loader("img/projectile2.png", renderer);
	enemy = Loader("img/nave2.png", renderer);
	
	SDL_Rect r;
	r.x = 100;
	r.y = 250;
	r.w = 100;
	r.h = 100;

	SDL_Rect enemySq;
	enemySq.x = 500;
	enemySq.y = 250;
	enemySq.w = 100;
	enemySq.h = 100;

	SDL_Rect sprite[2];
	for (int i = 0; i < 2; i++) {
		sprite[i].w = 100;
		sprite[i].h = 100;
		sprite[i].x = 100;
		sprite[i].y = 0;
	}

	SDL_Rect bullet[12]; //init all bullets
	for (int i = 0; i < 12; i++) {
		bullet[i] = { NULL, -200, 72, 100};
	}

	SDL_Rect bullet2[12]; //init all bullets enemies
	for (int i = 0; i < 12; i++) {
		bullet2[i] = { NULL, -200, 72, 100 };
	}

	int i = 0; 
	int k = 0;

	bool isDead = false;
	bool isDead2 = false;
	bool fire = false;
	bool quit = false;
	SDL_Event e;

	Mix_PlayMusic(music, -1);
	
	int timer = 0; 
	int timer2 = 0; 
	int timerdeath = 0;
	int timerdeath2 = 0;
	int lifecount[2] = { 6,6 };

	while (!quit) { //Game Loop
		timer++;
		k++;
		k = k % 20; 
		while (SDL_PollEvent(&e) != 0) {	//KILLS PROGRAM WHEN CLICKING [X] or ESC
			if (e.type == SDL_QUIT || keystate[SDL_SCANCODE_ESCAPE]) {
				quit = true;
			}
		}
		
		SDL_RenderCopy(renderer, bg, NULL, NULL);
		
		if (keystate[SDL_SCANCODE_SPACE] && timer > 45) {
			if (Mix_PlayChannel(-1, guns, 0) == -1) {
				printf("Mix_PlayChannel: %s\n", Mix_GetError());
				return 7;
			}
			fire = true;
			bullet[i].x = r.x + 100;
			bullet[i].y = r.y ;
			i++;
			i = i % 12;
			timer = 0;
		}

		if (keystate[SDL_SCANCODE_KP_PLUS] && timer > 45) {
			if (Mix_PlayChannel(-1, guns, 0) == -1) {
				printf("Mix_PlayChannel: %s\n", Mix_GetError());
				return 7;
			}
			fire = true;
			bullet2[i].x = enemySq.x;
			bullet2[i].y = enemySq.y;
			i++;
			i = i % 12;
			timer = 0;
		}
		
		if (fire) {
			for (int j = 0; j < 12; j++) {
				if (bullet[j].x < SCREEN_WIDTH && bullet[j].y > 0) {

					if (collide(bullet[j], enemySq) && !isDead2) {
						sprite[0].x = 0;
						if (lifecount[0] == 0) {
							isDead2 = true;
						}
						else {
							lifecount[0]--;
						}

						if (Mix_PlayChannel(-1, boom, 0) == -1) {
							printf("Mix_PlayChannel: %s\n", Mix_GetError());
							return 7;
						}
					}
					if (k > 10) {
						//SDL_RenderCopyEx(renderer, projectile, NULL, &bullet[j], NULL, NULL, SDL_FLIP_HORIZONTAL);
						SDL_RenderCopy(renderer, projectile, NULL, &bullet[j]);
					}
					else {
						SDL_RenderCopy(renderer, projectile2, NULL, &bullet[j]);
					}
					bullet[j].x += 5;
				}
			}
			for (int j = 0; j < 12; j++) {
				if (bullet2[j].x < SCREEN_WIDTH && bullet2[j].y > 0) { //P2 bullets

					if (collide(bullet2[j], r) && !isDead) {
						sprite[1].x = 0;
						if (lifecount[1] == 0) {
							isDead = true;
						}
						else {
							lifecount[1]--;
						}

						if (Mix_PlayChannel(-1, boom, 0) == -1) {
							printf("Mix_PlayChannel: %s\n", Mix_GetError());
							return 7;
						}
					}
					if (k > 10) {
						SDL_RenderCopyEx(renderer, projectile, NULL, &bullet2[j], NULL, NULL, SDL_FLIP_HORIZONTAL);
						
					}
					else {
						SDL_RenderCopyEx(renderer, projectile2, NULL, &bullet2[j], NULL, NULL, SDL_FLIP_HORIZONTAL);
					}
					bullet2[j].x -= 5;
				}
			}
		}

		//if (!isDead) {
			if (keystate[SDL_SCANCODE_W]) { r.y -= 3; }
			if (keystate[SDL_SCANCODE_A]) { r.x -= 3; }
			if (keystate[SDL_SCANCODE_S]) { r.y += 3; }
			if (keystate[SDL_SCANCODE_D]) { r.x += 3; }
			//Los portatiles tienen la culpa de que no lea todos los inputs a la vez.
		
		//if (!isDead2) {
			if (keystate[SDL_SCANCODE_UP]) { enemySq.y -= 3; }
			if (keystate[SDL_SCANCODE_DOWN]) { enemySq.y += 3; }
			if (keystate[SDL_SCANCODE_LEFT]) { enemySq.x -= 3; }
			if (keystate[SDL_SCANCODE_RIGHT]) { enemySq.x += 3; }
		

		if (isDead) {
			timerdeath++;
		}
		if (isDead2) {
			timerdeath2++;
		}

		
		
		if (timerdeath2 < 60) {
			SDL_RenderCopy(renderer, enemy, &sprite[0], &enemySq);
		}
		if (timerdeath < 60) {
			if (SDL_RenderCopyEx(renderer, ship, &sprite[1], &r, NULL, NULL, SDL_FLIP_HORIZONTAL) < 0) {
				const char* a = SDL_GetError();
				OutputDebugString(a);
			}
		}
		SDL_RenderPresent(renderer);
	}
	
	window = NULL;
	renderer = NULL;
	SDL_DestroyWindow(window);
	SDL_DestroyTexture(bg);
	SDL_DestroyTexture(projectile);
	SDL_DestroyTexture(projectile2);
	SDL_DestroyTexture(ship);
	SDL_DestroyTexture(enemy);

	Mix_CloseAudio();
	SDL_Quit();
	IMG_Quit();
	Mix_Quit();
	return 0;
}