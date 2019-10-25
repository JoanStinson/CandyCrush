#ifndef __MODULESCENEGAME_H__
#define __MODULESCENEGAME_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "CandyGrid.h"
#include "ModuleInput.h"
#include "CandyMatch.h"

#define ROWS 6
#define COLS 5
#define CANDY_SIZE 62
#define XOFFSET 30
#define YOFFSET 120

struct SDL_Texture;

class ModuleSceneGame : public Module {
public:
	ModuleSceneGame(bool start_enabled = true);
	~ModuleSceneGame();

	bool Start() override;
	update_status Update() override;
	update_status LateUpdate() override;
	bool CleanUp() override;

private:
	SDL_Texture *backgroundTexture = nullptr;
	SDL_Rect background;
	SDL_Texture *candiesTexture = nullptr;
	CandyGrid *candyGrid = nullptr;
	iPoint *selectedPoint = nullptr;

private:
	SDL_Rect GetRectFromCandy(Candy *candy);
	void OnMouseClick(iPoint mousePos);
	void OnMouseUnClick(iPoint mousePos);
	Candy* GetNextCandy(Candy *selectedCandy, MouseMove move);
	void HandleMatch(Candy *selectedCandy, Candy *nextCandy, CandyMatch match);
};

#endif // __MODULESCENEGAME_H__