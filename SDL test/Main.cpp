#include <iostream>
#include <stdio.h>
#include "SDL/include/SDL.h"
#include "SDL/include/SDL_image.h"
#include "SDL_mixer/include/SDL_mixer.h"

#pragma comment (lib, "SDL/Lib/SDL2main.lib")
#pragma comment (lib, "SDL/Lib/SDL2.lib")
#pragma comment (lib, "SDL/Lib/SDL2_image.lib")
#pragma comment (lib, "SDL/lib/x86/SDL2_mixer.lib")

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

	const Uint8 *keystate = SDL_GetKeyboardState(NULL);

	SDL_Renderer* renderer = NULL;
	

	SDL_Window* window = NULL;
	window = SDL_CreateWindow
	(
		"Se mueve la puta caja",
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
	
	bg = Loader("bg.png", renderer);
	ship = Loader("nave.png", renderer);
	projectile = Loader("projectile.png", renderer);

	SDL_Rect r;
	r.x = 270;
	r.y = 270;
	r.w = 200;
	r.h = 200;

	SDL_Rect bullet[30];
	for (int i = 0; i < 30; i++) {
		bullet[i] = { NULL, -200, 200, 200};
	}

	int i = 0; 
	
	bool fire = false;
	bool quit = false;
	SDL_Event e;

	int timer = 0; 
	while (!quit) { //KILLS PROGRAM WHEN CLICKING [X]
	
		timer++;
		while (SDL_PollEvent(&e) != 0) {	
			if (e.type == SDL_QUIT || keystate[SDL_SCANCODE_ESCAPE]) {
				quit = true;
			}
		}
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		
		SDL_RenderCopy(renderer, bg, NULL, NULL);

		SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
		
		
		if (keystate[SDL_SCANCODE_SPACE] && timer > 45) {
			
			fire = true;
			bullet[i].x = r.x + 100;
			bullet[i].y = r.y ;
			i++;
			i = i % 30;
			timer = 0;
		}
		
		if (fire) {
			for (int j = 0; j < 30; j++) {
				if (bullet[j].x < SCREEN_WIDTH) {
					SDL_RenderCopy(renderer, projectile, NULL, &bullet[j]);
					bullet[j].x += 5;
				}
			}
		}

		if (keystate[SDL_SCANCODE_UP]) { r.y -= 3; }
		if (keystate[SDL_SCANCODE_DOWN]) { r.y += 3; }
		if (keystate[SDL_SCANCODE_LEFT]) { r.x -= 3; }
		if (keystate[SDL_SCANCODE_RIGHT]) { r.x += 3; }


		SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
		SDL_RenderCopy(renderer, ship, NULL, &r);
		SDL_RenderPresent(renderer);
	}
	
	window = NULL;
	renderer = NULL;
	SDL_DestroyWindow(window);
	SDL_DestroyTexture(bg);

	SDL_Quit();
	IMG_Quit();

	return 0;
}