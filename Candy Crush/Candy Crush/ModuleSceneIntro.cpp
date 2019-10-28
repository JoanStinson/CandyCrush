#include "Globals.h"
#include "Application.h"
#include "ModuleSceneGame.h"
#include "ModuleSceneIntro.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModuleWindow.h"
#include "ModuleFadeToBlack.h"
#include <SDL.h>
#include "CEV_gif.h"
#include "CEV_gifDeflate.h"
#include "CEV_gifToSurface.h"

bool ModuleSceneIntro::hasPlayedIntro = false;
int ModuleSceneIntro::counter = 0;

ModuleSceneIntro::ModuleSceneIntro(bool start_enabled) : Module(start_enabled) {
	mainMenu = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
}

ModuleSceneIntro::~ModuleSceneIntro() {
}

// Load assets
bool ModuleSceneIntro::Start() {
	LOG("Loading intro scene");

	if (!hasPlayedIntro) {
		cinematic.anim = CEV_gifAnimLoad("Game/cinematic.gif", App->renderer->renderer);
		cinematic.texture = CEV_gifTexture(cinematic.anim);
		CEV_gifLoopMode(cinematic.anim, GIF_ONCE_FOR);
	}
	else {
		SDL_SetWindowSize(App->window->window, SCREEN_WIDTH, SCREEN_HEIGHT);
		girl.anim = CEV_gifAnimLoad("Game/girl.gif", App->renderer->renderer);
		girl.texture = CEV_gifTexture(girl.anim);
		CEV_gifLoopMode(girl.anim, GIF_REPEAT_FOR);

		graphics = App->textures->LoadImage("Game/main menu.jpg");
		App->audio->PlayMusic("Game/main menu.ogg");
	}

	return true;
}

// UnLoad assets
bool ModuleSceneIntro::CleanUp() {
	LOG("Unloading intro scene");

	App->textures->Unload(graphics);

	return true;
}

// Update: draw background
update_status ModuleSceneIntro::Update() {

	static float cinematicTime = 6.5F;
	currentTime = SDL_GetTicks();

	if (currentTime > lastTime + 1000 && counter >= 0) {
		//printf("Second: %d\n", currentTime / 1000);
		++counter;
		lastTime = currentTime;
	}

	if (!hasPlayedIntro) {
		if (counter >= cinematicTime) {
			hasPlayedIntro = true;
			SDL_SetWindowSize(App->window->window, SCREEN_WIDTH, SCREEN_HEIGHT);
			App->fade->FadeToBlack(App->scene_intro, App->scene_intro, 3.0F);
			return UPDATE_CONTINUE;
		}
		else {
			CEV_gifAnimAuto(cinematic.anim);
			App->renderer->Blit(cinematic.texture, 0, 0, nullptr);
		}
	}
	else if (counter >= cinematicTime + 2.5F) {
		App->renderer->Blit(graphics, 0, 0, &mainMenu, LAYER_BACK);

		CEV_gifAnimAuto(girl.anim);
		App->renderer->Blit(girl.texture, SCREEN_WIDTH / 2 - 270, 220, nullptr, LAYER_FRONT);
	}

	if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN || App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN) {
		App->fade->FadeToBlack(App->scene_game, App->scene_intro, 3.0F);
		SDL_SetWindowSize(App->window->window, SCREEN_WIDTH, SCREEN_HEIGHT);
	}

	return UPDATE_CONTINUE;
}
