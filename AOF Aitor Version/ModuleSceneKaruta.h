#ifndef __MODULESCENEHONDA_H__
#define __MODULESCENEHONDA_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

struct SDL_Texture;

class ModuleSceneKaruta : public Module
{
public:
	ModuleSceneKaruta();
	~ModuleSceneKaruta();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* graphics = nullptr;
	SDL_Rect background;
};

#endif // __MODULESCENEHONDA_H__