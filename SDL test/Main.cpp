#include <iostream>
#include <stdio.h>
#include "SDL/include/SDL.h"

#include "covadonga.h"

#pragma comment (lib, "SDL/Lib/SDL2main.lib")
#pragma comment (lib, "SDL/Lib/SDL2.lib")



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

/*
SDL_Surface* loadSurface(std::string path) {
	SDL_Surface* loadedSurface = SDL_LoadBMP;
}
*/
bool init(){
	bool success = true;
	
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL_Error: %s\n", SDL_GetError());
		success = false;
	}
	else {
		window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL) {
			printf("SDL_Error: %s\n", SDL_GetError());
			success = false;
		}
		else{
			screenSurface = SDL_GetWindowSurface(window); 
		}
	}
	screenSurface = SDL_GetWindowSurface(window);
	return success; 
}
/*
bool loadmedia() {
	bool success = true; 
	box = SDL_LoadBMP("pene.bmp");
	if (box == NULL) {
		printf("SDL_Error: %s\n", SDL_GetError());
		success = false;
	}
	return success;
} */

void Square() {
	//bool success = true;

	box = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	SDL_SetRenderDrawColor(box, 255, 0, 0, 255);

	SDL_RenderClear(box);

	
	
	SDL_SetRenderDrawColor(box, 0, 0, 255, 255);

	SDL_RenderFillRect(box, &r);

	SDL_RenderPresent(box);
}

void close() {
	//SDL_FreeSurface(File);

	box = NULL;
	SDL_DestroyWindow(window);
	window = NULL;
	SDL_Quit();
}



int main(int argc, char* argv[])
{
	
	test();
	/*
	bool quit = false;
	SDL_Event e;
	if (!init()) { return 1; }


	
	while (!quit) { //KILLS PROGRAM WHEN CLICKING [X]
		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT) {
				quit = true;
			}
			else if (e.type == SDL_KEYDOWN) {
				switch (e.key.keysym.sym) { //What, the actual, FUCK
				
				case SDLK_UP:
					r.y += 5;
					break;
				case SDLK_DOWN:
					r.y -= 5;
					break;
				case SDLK_RIGHT:
					r.x += 5;
					break;
				case SDLK_LEFT:
					r.x -= 5;
					break;
				}
			}
		}
		
		Square();
		SDL_BlitSurface(screenSurface, NULL, screenSurface, NULL);
		SDL_UpdateWindowSurface(window);
	}

	close();*/
	return 0;
}