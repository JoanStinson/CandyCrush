#ifndef _MODULESCENEGAME_H_
#define _MODULESCENEGAME_H_
#include "Module.h"
#include "Animation.h"
#include "CandyGrid.h"
#include "CandyMatch.h"

#define ROWS 6
#define COLS 5
#define MAX_MOVES 20
#define TARGET 4000

struct SDL_Texture;
struct Text;
typedef enum class MouseMove;

class ModuleSceneGame : public Module {
public:
	ModuleSceneGame(bool start_enabled = true);
	~ModuleSceneGame();

	bool Start() override;
	update_status Update() override;
	update_status LateUpdate() override;
	bool CleanUp() override;

private:
	SDL_Texture *candiesTexture = nullptr;
	SDL_Texture *backgroundTexture = nullptr;
	SDL_Rect background;
	CandyGrid *candyGrid = nullptr;
	iPoint *selectedPoint = nullptr;
	Text *targetText = nullptr;
	Text *targetNumText = nullptr;
	Text *movesText = nullptr;
	Text *movesNumText = nullptr;
	Text *scoreText = nullptr;
	Text *scoreNumText = nullptr;
	int moves = MAX_MOVES;
	int score = 0;

private:
	SDL_Rect GetRectFromCandy(Candy *candy);
	void OnMouseClick(iPoint mousePos);
	void OnMouseUnClick(iPoint mousePos);
	Candy* GetNextCandy(Candy *selectedCandy, MouseMove move);
	void HandleMatch(Candy *selectedCandy, Candy *nextCandy, CandyMatch match);
};

#endif 