#ifndef __MODULESCENEGAME_H__
#define __MODULESCENEGAME_H__

#include "Module.h"
#include "Animation.h"
#include "CandyGrid.h"
#include "CandyMatch.h"
#include "CandyScore.h"
#include "SDL_Button.h"

#define ROWS 6
#define COLS 5
#define MAX_MOVES 20
#define TARGET 1000

struct SDL_Texture;
struct SDL_Rect;
struct Text;
typedef enum MouseMove;

class ModuleSceneGame : public Module {
public:
	ModuleSceneGame(bool start_enabled = true);
	~ModuleSceneGame();

	bool Start() override;
	update_status Update() override;
	update_status LateUpdate() override;
	bool CleanUp() override;

private:
	SDL_Rect GetRectFromCandy(Candy *candy);
	void OnMouseClick(iPoint mousePos);
	void OnMouseUnClick(iPoint mousePos);
	Candy* GetNextCandy(Candy *selectedCandy, MouseMove move);
	void HandleMatch(Candy *selectedCandy, Candy *nextCandy, CandyMatch match);

	void Initialize();
	void OnRetryClick();

private:
	SDL_Rect background;
	CandyScore candyScore;

	CandyGrid* candyGrid = nullptr;
	iPoint* selectedPoint = nullptr;
	SDL_Button_t* retryButton = nullptr;

	SDL_Texture* buttonTexture = nullptr;
	SDL_Texture* candiesTexture = nullptr;
	SDL_Texture* backgroundTexture = nullptr;
	SDL_Texture* blackTexture = nullptr;

	Text* targetText = nullptr;
	Text* targetNumText = nullptr;
	Text* movesText = nullptr;
	Text* movesNumText = nullptr;
	Text* scoreText = nullptr;
	Text* scoreNumText = nullptr;
	Text* gameOverText = nullptr;
	Text* winText = nullptr;

	int moves = MAX_MOVES;
	int score = 0;
	bool gameOver = false;
	bool win = false;
};

#endif // __MODULESCENEGAME_H__