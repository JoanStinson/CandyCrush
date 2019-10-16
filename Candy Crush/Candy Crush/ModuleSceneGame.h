#ifndef __MODULESCENEGAME_H__
#define __MODULESCENEGAME_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

#define CANDY_SIZE 62
#define ROWS 6
#define COLS 5

struct SDL_Texture;

class ModuleSceneGame : public Module {
public:
	ModuleSceneGame(bool start_enabled = true);
	~ModuleSceneGame();

	bool Start() override;
	update_status Update() override;
	update_status LateUpdate() override;
	bool CleanUp() override;

public:

	SDL_Texture *graphics = nullptr;
	SDL_Rect background;

	SDL_Texture *candies = nullptr;
	SDL_Rect red;
	SDL_Rect orange;
	SDL_Rect yellow;
	SDL_Rect green;
	SDL_Rect blue;
	SDL_Rect purple;

	int **tablero = nullptr;

};

#endif // __MODULESCENEGAME_H__