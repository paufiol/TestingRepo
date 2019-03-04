#pragma once

#include "SDL/include/SDL.h"

#pragma comment (lib, "SDL/Lib/SDL2main.lib")
#pragma comment (lib, "SDL/Lib/SDL2.lib")

int test()
{
	SDL_Window* window = NULL;
	window = SDL_CreateWindow
	(
		"Se mueve la puta caja", SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		SDL_WINDOW_SHOWN
	);

	// Setup renderer
	SDL_Renderer* renderer = NULL;
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	// Set render color to red ( background will be rendered in this color )
	//SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

	// Clear winow
	SDL_RenderClear(renderer);

	// Creat a rect at pos ( 50, 50 ) that's 50 pixels wide and 50 pixels high.
	SDL_Rect r;
	r.x = 50;
	r.y = 50;
	r.w = 50;
	r.h = 50;

	// Set render color to blue ( rect will be rendered in this color )
	//SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);

	// Render rect
	//SDL_RenderFillRect(renderer, &r);

	// Render the rect to the screen
	//SDL_RenderPresent(renderer);

	bool quit = false;
	SDL_Event e;
	while (!quit) { //KILLS PROGRAM WHEN CLICKING [X]
		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT) {
				quit = true;
			}
			else if (e.type == SDL_KEYDOWN) {
				switch (e.key.keysym.sym) { //What, the actual, FUCK

				case SDLK_UP:
					r.y -= 5;
					break;
				case SDLK_DOWN:
					r.y += 5;
					break;
				case SDLK_RIGHT:
					r.x += 5;
					break;
				case SDLK_LEFT:
					r.x -= 5;
					break;
				}
			}

			SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
			SDL_RenderClear(renderer);
			SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
			SDL_RenderFillRect(renderer, &r);
			SDL_RenderPresent(renderer);
		}
	}
	window = NULL;
	renderer = NULL;
	SDL_DestroyWindow(window);

	SDL_Quit();

	return EXIT_SUCCESS;
}