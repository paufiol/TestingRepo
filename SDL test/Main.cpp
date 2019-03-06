#include <iostream>

#include "SDL/include/SDL.h"
#include "SDL/include/SDL_image.h"


#pragma comment (lib, "SDL/Lib/SDL2main.lib")
#pragma comment (lib, "SDL/Lib/SDL2.lib")
#pragma comment (lib, "SDL/lib/SDL2_image.lib")


using namespace std;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;



enum KeyPressSurfaces //creates constants starting from 0 in succession.
{
	KEY_PRESS_SURFACE_DEFAULT,
	KEY_PRESS_SURFACE_UP,
	KEY_PRESS_SURFACE_DOWN,
	KEY_PRESS_SURFACE_LEFT,
	KEY_PRESS_SURFACE_RIGHT,
	KEY_PRESS_SURFACE_TOTAL
};

bool KeyRepeat(SDL_Event e) {
	bool ispressed = false;
	if (e.type == SDL_KEYDOWN) {
		ispressed = true; 
	}
	return ispressed;
}


int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_VIDEO);
	
	IMG_Init(IMG_INIT_PNG);

	const int SCREEN_WIDTH = 640;
	const int SCREEN_HEIGHT = 640;

	const Uint8 *keystate = SDL_GetKeyboardState(NULL);

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

	SDL_Renderer* renderer = NULL;
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);

	SDL_RenderClear(renderer);

	SDL_Rect r;
	r.x = 270;
	r.y = 270;
	r.w = 100;
	r.h = 100;

	SDL_Rect bullet[30];
	for (int i = 0; i < 30; i++) {
		bullet[i] = { NULL, -20, 50, 15 };
	}
	
	
	bool up = false, down = false, right = false, left = false;

	int i = 0; 
	
	bool fire = false;
	bool quit = false;
	SDL_Event e;

	int timer = 0; 
	while (!quit) { //KILLS PROGRAM WHEN CLICKING [X]
	
		timer++;
		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT) {
				quit = true;
			}
			if(e.key.keysym.sym == SDLK_SPACE){
				if (e.type == SDL_KEYDOWN && timer > 20) {
				fire = true;
				bullet[i].x = r.x + 45;
				bullet[i].y = r.y + 45;							
				i++;
				i = i % 30;
				timer = 0;
				}
			break;
			}
		
		}
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		SDL_RenderClear(renderer);

		SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
		
		if (fire) {
			for (int j = 0; j < 30; j++) {
				if (bullet[j].x < 640) {
					SDL_RenderFillRect(renderer, &bullet[j]);
					bullet[j].x += 5;
				}
			}
		}

		//if (keystate[SDL_SCANCODE_SPACE]) { bullet -= 3; }
		if (keystate[SDL_SCANCODE_UP]) { r.y -= 3; }
		if (keystate[SDL_SCANCODE_DOWN]) { r.y += 3; }
		if (keystate[SDL_SCANCODE_LEFT]) { r.x -= 3; }
		if (keystate[SDL_SCANCODE_RIGHT]) { r.x += 3; }


		SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
		SDL_RenderFillRect(renderer, &r);
		SDL_RenderPresent(renderer);
	}
	window = NULL;
	renderer = NULL;
	SDL_DestroyWindow(window);


	SDL_Quit();
	IMG_Quit();



	return 0;
}