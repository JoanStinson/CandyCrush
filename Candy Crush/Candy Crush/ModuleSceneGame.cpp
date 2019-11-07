#include "ModuleSceneGame.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleWindow.h"
#include "ModuleFadeToBlack.h"
#include <SDL.h>
#include <string>

#define SPRITE_LEVEL "Game/level.jpg"
#define SPRITE_CANDIES "Game/candy spritesheet.png"
#define MUSIC_LEVEL "Game/level.ogg"
#define CANDY_SIZE 62
#define XOFFSET 30
#define YOFFSET 120

ModuleSceneGame::ModuleSceneGame(bool start_enabled) : Module(start_enabled) {
	background = { 0, 0, 375, 667 };
}

ModuleSceneGame::~ModuleSceneGame() {

	delete candyGrid;
	delete selectedPoint;
	delete targetText;
	delete targetNumText;
	delete movesText;
	//delete movesNumText;
	delete scoreText;
	//delete scoreNumText;
	delete gameOverText;
	delete winText;
	delete retryButton;
}

bool ModuleSceneGame::Start() {
	LOG("Loading game scene");
	candyGrid = new CandyGrid(ROWS, COLS);
	backgroundTexture = App->textures->LoadImage(SPRITE_LEVEL);
	candiesTexture = App->textures->LoadImage(SPRITE_CANDIES);
	App->audio->PlayMusic(MUSIC_LEVEL);
	targetText = new Text(App->textures->LoadText("Target: "));
	targetNumText = new Text(App->textures->LoadText(std::to_string(TARGET).c_str()));
	movesText = new Text(App->textures->LoadText("Moves: ", 20));
	scoreText = new Text(App->textures->LoadText("Score: "));
	gameOverText = new Text(App->textures->LoadText("Game Over", 50, SDL_Color{ 255, 0, 255 }));
	winText = new Text(App->textures->LoadText("You Win!", 50, SDL_Color{ 255, 255, 0 }));

	SDL_Rect bg = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	SDL_Surface *s = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32, 0, 0, 0, 0);
	SDL_FillRect(s, &bg, SDL_MapRGB(s->format, 0, 0, 0));
	bgTexture = SDL_CreateTextureFromSurface(App->renderer->renderer, s);
	SDL_SetTextureBlendMode(bgTexture, SDL_BLENDMODE_BLEND);
	SDL_SetTextureAlphaMod(bgTexture, 200);

	SDL_Rect buttonRect = { 0, 0, 100, 100 };
	SDL_Surface *buttonS = SDL_CreateRGBSurface(0, 100, 100, 32, 0, 0, 0, 0);
	SDL_FillRect(buttonS, &buttonRect, SDL_MapRGB(buttonS->format, 255, 165, 0));
	retryButton = SDL_Button(buttonS, 140, 380, 100, 100);
	buttonTexture = SDL_CreateTextureFromSurface(App->renderer->renderer, retryButton->internal_surface);
	return true;
}

bool ModuleSceneGame::CleanUp() {
	LOG("Unloading game scene");
	App->textures->Unload(backgroundTexture);
	App->textures->Unload(candiesTexture);
	App->textures->Unload(buttonTexture);
	App->textures->Unload(bgTexture);
	return true;
}

SDL_Rect ModuleSceneGame::GetRectFromCandy(Candy *candy) {
	SDL_Rect image;
	switch (candy->GetType()) {
	case CandyType::RED:
		image = { 15, 201, CANDY_SIZE, CANDY_SIZE };
		break;
	case CandyType::ORANGE:
		image = { 108, 201, CANDY_SIZE, CANDY_SIZE };
		break;
	case CandyType::YELLOW:
		image = { 202, 201, CANDY_SIZE, CANDY_SIZE };
		break;
	case CandyType::GREEN:
		image = { 295, 201, CANDY_SIZE, CANDY_SIZE };
		break;
	case CandyType::BLUE:
		image = { 389, 201, CANDY_SIZE, CANDY_SIZE };
		break;
	case CandyType::PURPLE:
		image = { 481, 201, CANDY_SIZE, CANDY_SIZE };
		break;
	default:
		break;
	}
	return image;
}

void ModuleSceneGame::OnMouseClick(iPoint mousePos) {
	const int xEnd = (CANDY_SIZE * COLS) + XOFFSET;
	const int yEnd = (CANDY_SIZE * ROWS) + YOFFSET;

	if (win || gameOver) {
		if (mouse_on_button(retryButton->location_and_size, mousePos.x, mousePos.y)) {
			OnRetryClick();
			LOG("Retried\n");
		}
	}
	else if (mousePos.x >= XOFFSET && mousePos.x <= xEnd && mousePos.y >= YOFFSET && mousePos.y <= yEnd) {
		selectedPoint = new iPoint(mousePos);
	}
}

void ModuleSceneGame::OnMouseUnClick(iPoint mousePos) {
	if (selectedPoint != nullptr) {
		iPoint mouseDif = mousePos - *selectedPoint;
		MouseMove move = abs(mouseDif.x) > abs(mouseDif.y) ? (mouseDif.x < 0 ? MouseMove::LEFT : MouseMove::RIGHT) : (mouseDif.y < 0 ? MouseMove::UP : MouseMove::DOWN);

		int selectedRow = (selectedPoint->y - YOFFSET) / CANDY_SIZE;
		int selectedCol = (selectedPoint->x - XOFFSET) / CANDY_SIZE;

		Candy *selectedCandy = candyGrid->Get(iPoint(selectedRow, selectedCol));
		Candy *nextCandy = GetNextCandy(selectedCandy, move);

		if (nextCandy != nullptr) {
			--moves;

			CandyType type = selectedCandy->GetType();
			iPoint pos = nextCandy->GetPos();

			CandyMatch match = candyGrid->CheckMatch(type, pos);
			HandleMatch(selectedCandy, nextCandy, match);
		}

		if (moves == 0) {
			gameOver = true;
		}

		selectedPoint = nullptr;
	}
}

Candy* ModuleSceneGame::GetNextCandy(Candy *selectedCandy, MouseMove move) {
	Candy *nextCandy = nullptr;
	iPoint nextPos = selectedCandy->GetPos();

	switch (move) {
	case MouseMove::UP:
		nextPos.x--;
		break;

	case MouseMove::DOWN:
		nextPos.x++;
		break;

	case MouseMove::RIGHT:
		nextPos.y++;
		break;

	case MouseMove::LEFT:
		nextPos.y--;
		break;
	}

	if (nextPos.x >= 0 && nextPos.x < ROWS && nextPos.y >= 0 && nextPos.y < COLS) {
		nextCandy = candyGrid->Get(nextPos);
	}

	return nextCandy;
}

void ModuleSceneGame::HandleMatch(Candy *selectedCandy, Candy *nextCandy, CandyMatch match) {

	if (match.GetMatch() != Match::NONE) {
		// Swap candies
		candyGrid->Swap(selectedCandy->GetPos(), nextCandy->GetPos());

		// Clear candies
		candyGrid->ClearFromMatch(selectedCandy, match);

		// Update score
		score += candyScore.GetScore(match.GetMatches().x);
		score += candyScore.GetScore(match.GetMatches().y);
		if (score >= TARGET)
			win = true;

		// Clear grid
		//bool matched = true;
		//while (matched) {
		candyGrid->ClearGrid();
		//}
	}
}

update_status ModuleSceneGame::Update() {

	// Draw background
	App->renderer->Blit(backgroundTexture, 0, 0, &background);

	// Draw candies
	for (int i = 0; i < ROWS; ++i)
		for (int j = 0; j < COLS; ++j)
			App->renderer->Blit(candiesTexture, (CANDY_SIZE * j) + XOFFSET, (CANDY_SIZE * i) + YOFFSET, &GetRectFromCandy(candyGrid->Get(iPoint(i, j))));

	// Draw text
	App->renderer->Blit(targetText->texture, (SCREEN_WIDTH / 2) - (targetText->rect.w / 2) + 60, 13, &targetText->rect);
	App->renderer->Blit(targetNumText->texture, (SCREEN_WIDTH / 2) - (targetNumText->rect.w / 2) + 130, 13, &targetNumText->rect);
	App->renderer->Blit(movesText->texture, (SCREEN_WIDTH / 2) - 42, SCREEN_HEIGHT - 97, &movesText->rect);
	moves < 10 ? movesNumText = new Text(App->textures->LoadText((std::to_string(0) + std::to_string(moves)).c_str(), 26)) : movesNumText = new Text(App->textures->LoadText(std::to_string(moves).c_str(), 26));
	App->renderer->Blit(movesNumText->texture, (SCREEN_WIDTH / 2) - 25, SCREEN_HEIGHT - 80, &movesNumText->rect);
	App->renderer->Blit(scoreText->texture, (SCREEN_WIDTH / 2) + 87, SCREEN_HEIGHT - 100, &scoreText->rect);
	score < 10 ? scoreNumText = new Text(App->textures->LoadText((std::to_string(0) + std::to_string(0) + std::to_string(0) + std::to_string(0) + std::to_string(score)).c_str(), 30)) :
		score < 100 ? scoreNumText = new Text(App->textures->LoadText((std::to_string(0) + std::to_string(0) + std::to_string(0) + std::to_string(score)).c_str(), 30)) :
		score < 1000 ? scoreNumText = new Text(App->textures->LoadText((std::to_string(0) + std::to_string(0) + std::to_string(score)).c_str(), 30)) :
		score < 10000 ? scoreNumText = new Text(App->textures->LoadText((std::to_string(0) + std::to_string(score)).c_str(), 30)) : scoreNumText = new Text(App->textures->LoadText((std::to_string(score)).c_str(), 30));
	App->renderer->Blit(scoreNumText->texture, (SCREEN_WIDTH / 2) + 80, SCREEN_HEIGHT - 80, &scoreNumText->rect);

	// Mouse events
	App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN ? OnMouseClick(App->input->GetMousePosition()) :
		App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_UP ? OnMouseUnClick(App->input->GetMousePosition()) : NULL;

	// Win screen
	if (win) {
		App->renderer->Blit(bgTexture, 0, 0, NULL);
		App->renderer->Blit(winText->texture, (SCREEN_WIDTH / 2) - (targetText->rect.w / 2) - targetText->rect.w, (SCREEN_HEIGHT / 2) - (targetText->rect.h / 2), &winText->rect);
		App->renderer->Blit(buttonTexture, 140, 380, nullptr);
	}
	// Game over screen
	else if (gameOver) {
		App->renderer->Blit(bgTexture, 0, 0, NULL);
		App->renderer->Blit(gameOverText->texture, (SCREEN_WIDTH / 2) - (targetText->rect.w / 2) - targetText->rect.w, (SCREEN_HEIGHT / 2) - (targetText->rect.h / 2), &gameOverText->rect);
		App->renderer->Blit(buttonTexture, 140, 380, nullptr);
	}

	// Change scene
	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
		App->fade->FadeToBlack(App->sceneIntro, App->sceneGame, 3.0F);

	return UPDATE_CONTINUE;
}

update_status ModuleSceneGame::LateUpdate() {
	delete movesNumText;
	delete scoreNumText;
	return UPDATE_CONTINUE;
}

void ModuleSceneGame::Initialize() {
	candyGrid = new CandyGrid(ROWS, COLS);
	moves = MAX_MOVES;
	score = 0;
	gameOver = false;
	win = false;
}

void ModuleSceneGame::OnRetryClick() {
	Initialize();
}
