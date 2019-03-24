#include "Globals.h"
#include "Application.h"
#include "ModuleWindow.h"

// TODO 2: Init the library and check for possible error
// using SDL_GetError()



bool ModuleWindow::Init()
{

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		LOG(SDL_GetError());
		return false;
	}

	window = SDL_CreateWindow
	(
		"Test",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		SDL_WINDOW_SHOWN
	);


	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);


	if ((renderer != NULL) && (window != NULL)) {
		LOG(SDL_GetError());
		return true;
	}
	else {
		return false;
	}
}

bool ModuleWindow::CleanUp()
{
	renderer = NULL;
	window = NULL;

	SDL_DestroyWindow(window);

	SDL_Quit();
	return true;

}

// TODO 3: pick the width and height and experiment with flags: borderless / fullscreen / resizable,
// then create the window and check for errors

// TODO 4: Finally create a screen surface and keep it as a public variable

// TODO 5: Fill with code CleanUp() method :)

