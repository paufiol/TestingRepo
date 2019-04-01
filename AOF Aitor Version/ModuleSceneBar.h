#ifndef __MODULESCENEBAR_H__
#define __MODULESCENEBAR_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

struct SDL_Texture;

class ModuleSceneBar : public Module
{
public:
	ModuleSceneBar();
	~ModuleSceneBar();

	bool Start();
	update_status Update();
	bool CleanUp();

public:
	
	SDL_Texture* graphics = nullptr;
	SDL_Rect background;


	float foreground_pos;
	bool forward;
};

#endif // __MODULESCENEKEN_H__