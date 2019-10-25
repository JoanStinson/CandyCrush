#include "Application.h"
#include "ModuleSceneGame.h"
#include "ModuleSceneIntro.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"

#include "ModuleAudio.h"
#include "ModuleFadeToBlack.h"
#include "SDL2/include/SDL.h"

ModuleSceneGame::ModuleSceneGame(bool start_enabled) : Module(start_enabled) {
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

	if (mousePos.x >= XOFFSET && mousePos.x <= xEnd && mousePos.y >= YOFFSET && mousePos.y <= yEnd) {
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
			CandyType type = selectedCandy->GetType();
			iPoint pos = nextCandy->GetPos();

			CandyMatch match = candyGrid->CheckMatch(type, pos);
			printf("%d\n", match);

			HandleMatch(selectedCandy, nextCandy, match);
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

		candyGrid->Swap(selectedCandy->GetPos(), nextCandy->GetPos());

		switch (match.GetMatch()) {
		case Match::ROW:
			candyGrid->ClearMatchedRow(match.GetYBegin(), match.GetYEnd());
			break;

		case Match::COL:
			candyGrid->ClearMatchedCol(match.GetXBegin(), match.GetXEnd());
			break;

		case Match::BOTH:
			candyGrid->ClearMatchedRow(match.GetYBegin(), match.GetYEnd());
			candyGrid->ClearMatchedCol(match.GetXBegin(), match.GetXEnd());
			break;
		}
	}

}

// Update: draw background
update_status ModuleSceneGame::Update() {

	// Draw background
	App->renderer->Blit(backgroundTexture, 0, 0, &background, LAYER_BACK);

	// Draw candies
	for (int i = 0; i < ROWS; ++i) {
		for (int j = 0; j < COLS; ++j) {
			Candy *candy = candyGrid->Get(iPoint(i, j));
			App->renderer->Blit(candiesTexture, (CANDY_SIZE * j) + XOFFSET, (CANDY_SIZE * i) + YOFFSET, &GetRectFromCandy(candy), LAYER_FRONT);
		}
	}

	// Mouse events
	if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN)
		OnMouseClick(App->input->GetMousePosition());
	else if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_UP)
		OnMouseUnClick(App->input->GetMousePosition());

	// Change scene
	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
		App->fade->FadeToBlack(App->scene_intro, App->scene_game, 3.0F);

	return UPDATE_CONTINUE;
}

update_status ModuleSceneGame::LateUpdate() {
	return UPDATE_CONTINUE;
}
