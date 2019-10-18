#include "Application.h"
#include "ModuleSceneGame.h"
#include "ModuleSceneIntro.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModuleFadeToBlack.h"
#include "SDL2/include/SDL.h"

ModuleSceneGame::ModuleSceneGame(bool start_enabled) : Module(start_enabled) {
	// setup sprites
	background = { 0, 0, 375, 667 };
}

ModuleSceneGame::~ModuleSceneGame() {
	delete candyGrid;
}

// Load assets
bool ModuleSceneGame::Start() {
	LOG("Loading game scene");
	candyGrid = new CandyGrid(ROWS, COLS);
	backgroundTexture = App->textures->LoadImage("Game/level1.jpg");
	candiesTexture = App->textures->LoadImage("Game/candy spritesheet.png");
	App->audio->PlayMusic("Game/level1.ogg");
	return true;
}

// UnLoad assets
bool ModuleSceneGame::CleanUp() {
	LOG("Unloading game scene");

	App->textures->Unload(backgroundTexture);
	App->textures->Unload(candiesTexture);
	return true;
}

SDL_Rect ModuleSceneGame::GetRectFromCandy(Candy *candy) {
	SDL_Rect image;
	switch (candy->GetType()) {
	case CandyType::RED:
		image = { 15,	201, CANDY_SIZE, CANDY_SIZE };
		break;
	case CandyType::ORANGE:
		image = { 108,  201, CANDY_SIZE, CANDY_SIZE };
		break;
	case CandyType::YELLOW:
		image = { 202,  201, CANDY_SIZE, CANDY_SIZE };
		break;
	case CandyType::GREEN:
		image = { 295,  201, CANDY_SIZE, CANDY_SIZE };
		break;
	case CandyType::BLUE:
		image = { 389,  201, CANDY_SIZE, CANDY_SIZE };
		break;
	case CandyType::PURPLE:
		image = { 481,  201, CANDY_SIZE, CANDY_SIZE };
		break;
	default:
		break;
	}
	return image;
}

// Update: draw background
update_status ModuleSceneGame::Update() {

	App->renderer->Blit(backgroundTexture, 0, 0, &background, LAYER_BACK);

	// Draw candies
	const int xOffset = 30;
	const int yOffset = 120;

	for (int i = 0; i < ROWS; ++i) {
		for (int j = 0; j < COLS; ++j) {
			Candy *candy = candyGrid->Get(iPoint(i, j));
			App->renderer->Blit(candiesTexture, (CANDY_SIZE * j) + xOffset, (CANDY_SIZE * i) + yOffset, &GetRectFromCandy(candy), LAYER_FRONT);
		}
	}

	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
		App->fade->FadeToBlack(App->scene_intro, App->scene_game, 3.0F);

	return UPDATE_CONTINUE;
}

update_status ModuleSceneGame::LateUpdate() {

	return UPDATE_CONTINUE;
}
