#include <iostream>
#include <stdio.h>
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



SDL_Texture* Loader(const char* file, SDL_Renderer* renderer) {
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

int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_VIDEO);
	
	IMG_Init(IMG_INIT_PNG);

	Mix_Init(MIX_INIT_OGG);

	Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1048);

	Mix_Music* music = NULL;
	Mix_Chunk* guns = NULL; 

	Mix_VolumeMusic(32);

	music = Mix_LoadMUS("sound/ripandtear.ogg");
	if (!music) {
		printf("Mix_LoadMUS(\"music.mp3\"): %s\n", Mix_GetError());
		// this might be a critical error...
	}
	guns = Mix_LoadWAV("sound/laser.ogg");
	if (!guns) {
		printf("Mix_LoadMUS(\"music.mp3\"): %s\n", Mix_GetError());
		// this might be a critical error...
	}


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


	SDL_Surface* LoadSurf = NULL;
	SDL_Texture* bg = NULL;
	SDL_Texture* ship = NULL;
	SDL_Texture* projectile = NULL;
	SDL_Texture* projectile2 = NULL;

	bg = Loader("img/bg2.png", renderer);
	ship = Loader("img/nave.png", renderer);
	projectile = Loader("img/projectile1.png", renderer);
	projectile2 = Loader("img/projectile2.png", renderer);
	
	SDL_Rect r;
	r.x = 270;
	r.y = 270;
	r.w = 200;
	r.h = 200;

	SDL_Rect bullet[30]; //init all bullets
	for (int i = 0; i < 30; i++) {
		bullet[i] = { NULL, -200, 144, 200};
	}

	int i = 0; 
	int k = 0;

	bool fire = false;
	bool quit = false;
	SDL_Event e;

	Mix_PlayMusic(music, -1);
	int timer = 0; 
	while (!quit) { //Game Loop
		timer++;
		k++;
		k = k % 20; 
		while (SDL_PollEvent(&e) != 0) {	//KILLS PROGRAM WHEN CLICKING [X] or ESC
			if (e.type == SDL_QUIT || keystate[SDL_SCANCODE_ESCAPE]) {
				quit = true;
			}
		}
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		
		SDL_RenderCopy(renderer, bg, NULL, NULL);

		SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
		
		
		if (keystate[SDL_SCANCODE_SPACE] && timer > 45) {
			if (Mix_PlayChannel(-1, guns, 0) == -1) {
				printf("Mix_PlayChannel: %s\n", Mix_GetError());
				// may be critical error, or maybe just no channels were free.
				// you could allocated another channel in that case...
				return 7;
			}
			fire = true;
			bullet[i].x = r.x + 100;
			bullet[i].y = r.y ;
			i++;
			i = i % 30;
			timer = 0;
		}
		
		if (fire) {
			for (int j = 0; j < 30; j++) {
				if (bullet[j].x < SCREEN_WIDTH && bullet[j].y > 0) {
					if (k > 10) {
						SDL_RenderCopy(renderer, projectile, NULL, &bullet[j]);
					}
					else {
						SDL_RenderCopy(renderer, projectile2, NULL, &bullet[j]);
					}
					bullet[j].x += 5;
				}
			}
		}

		if (keystate[SDL_SCANCODE_UP]) { r.y -= 3; }
		if (keystate[SDL_SCANCODE_DOWN]) { r.y += 3; }
		if (keystate[SDL_SCANCODE_LEFT]) { r.x -= 3; }
		if (keystate[SDL_SCANCODE_RIGHT]) { r.x += 3; }
		//Los portatiles tienen la culpa de que no lea todos los inputs a la vez. COÑO

		SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
		SDL_RenderCopy(renderer, ship, NULL, &r);
		SDL_RenderPresent(renderer);
	}
	
	window = NULL;
	renderer = NULL;
	SDL_DestroyWindow(window);
	SDL_DestroyTexture(bg);
	SDL_DestroyTexture(projectile);
	SDL_DestroyTexture(projectile2);
	SDL_DestroyTexture(ship);

	Mix_CloseAudio();
	SDL_Quit();
	IMG_Quit();
	Mix_Quit();
	return 0;
}