#ifndef __ModuleWindow_H__
#define __ModuleWindow_H__

#include "SDL/include/SDL.h"


// TODO 1: Create the declaration of ModuleWindow class
class ModuleWindow : public Module {
public:
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	SDL_Surface* surface = NULL; 

	virtual bool Init() override;
	virtual bool CleanUp() override;
};

#endif // __ModuleWindow_H__