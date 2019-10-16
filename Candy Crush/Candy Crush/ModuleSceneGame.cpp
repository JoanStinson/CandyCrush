#include "Globals.h"
#include "Application.h"
#include "ModuleSceneGame.h"
#include "ModuleSceneIntro.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModuleFadeToBlack.h"
#include "SDL2/include/SDL.h"
#include <stdlib.h>
#include <time.h>

ModuleSceneGame::ModuleSceneGame(bool start_enabled) : Module(start_enabled) {
	// setup sprites
	background = { 0,0, 375, 667 };
	red =		{ 15,	201, CANDY_SIZE, CANDY_SIZE };
	orange =	{ 108,  201, CANDY_SIZE, CANDY_SIZE };
	yellow =	{ 202,  201, CANDY_SIZE, CANDY_SIZE };
	green =		{ 295,  201, CANDY_SIZE, CANDY_SIZE };
	blue =		{ 389,  201, CANDY_SIZE, CANDY_SIZE };
	purple =	{ 481,  201, CANDY_SIZE, CANDY_SIZE };

	// init tablero
	srand(static_cast<unsigned>(time(NULL)));
	tablero = new int*[ROWS]();
	for (int i = 0; i < ROWS; ++i) {
		tablero[i] = new int[COLS]();
	}

	// fill tablero
	for (int i = 0; i < ROWS; ++i) {
		for (int j = 0; j < COLS; ++j) {
			tablero[i][j] = rand() % 6 + 1;
		}
	}
}

ModuleSceneGame::~ModuleSceneGame() {
	delete[] tablero;
}

// Load assets
bool ModuleSceneGame::Start() {
	LOG("Loading game scene");
	
	graphics = App->textures->LoadImage("Game/level1.jpg");
	candies = App->textures->LoadImage("Game/candy spritesheet.png");
	App->audio->PlayMusic("Game/level1.ogg");
	return true;
}

// UnLoad assets
bool ModuleSceneGame::CleanUp() {
	LOG("Unloading game scene");

	App->textures->Unload(graphics);
	return true;
}

// Update: draw background
update_status ModuleSceneGame::Update() {

	App->renderer->Blit(graphics, 0, 0, &background, LAYER_BACK);

	// draw tablero with candies
	static int xOffset = 30;
	static int yOffset = 120;
	static int rows = 7;
	static int cols = 6;
	for (int i = 0; i < ROWS; ++i) {
		for (int j = 0; j < COLS; ++j) {
			int randNum = tablero[i][j];
			if (randNum == 1) App->renderer->Blit(candies, (CANDY_SIZE * j) + xOffset, (CANDY_SIZE * i) + yOffset, &red, LAYER_FRONT);
			else if (randNum == 2) App->renderer->Blit(candies, (CANDY_SIZE * j) + xOffset, (CANDY_SIZE * i) + yOffset, &orange, LAYER_FRONT);
			else if (randNum == 3) App->renderer->Blit(candies, (CANDY_SIZE * j) + xOffset, (CANDY_SIZE * i) + yOffset, &yellow, LAYER_FRONT);
			else if (randNum == 4) App->renderer->Blit(candies, (CANDY_SIZE * j) + xOffset, (CANDY_SIZE * i) + yOffset, &green, LAYER_FRONT);
			else if (randNum == 5) App->renderer->Blit(candies, (CANDY_SIZE * j) + xOffset, (CANDY_SIZE * i) + yOffset, &blue, LAYER_FRONT);
			else if (randNum == 6) App->renderer->Blit(candies, (CANDY_SIZE * j) + xOffset, (CANDY_SIZE * i) + yOffset, &purple, LAYER_FRONT);
		}
	}

	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
		App->fade->FadeToBlack(App->scene_intro, App->scene_game, 3.0F);

	return UPDATE_CONTINUE;
}

update_status ModuleSceneGame::LateUpdate() {

	return UPDATE_CONTINUE;
}
