#include "ModuleFadeToBlack.h"
#include "Application.h"
#include "ModuleRender.h"
#include <math.h>
#include <SDL.h>

ModuleFadeToBlack::ModuleFadeToBlack(bool start_enabled) : Module(start_enabled) {
}

ModuleFadeToBlack::~ModuleFadeToBlack() {
}

bool ModuleFadeToBlack::Start() {
	LOG("Preparing Fade Screen");
	SDL_SetRenderDrawBlendMode(App->renderer->renderer, SDL_BLENDMODE_BLEND);
	return true;
}

update_status ModuleFadeToBlack::PostUpdate() {
	if (startTime > 0) {
		Uint32 now = SDL_GetTicks() - startTime;
		float normalized = (float)now / (float)totalTime;

		if (normalized > 1.0F)
			normalized = 1.0F;

		if (fadingIn == false)
			normalized = 1.0F - normalized;

		// Draw a screen-size balck rectangle with alpha
		SDL_SetRenderDrawColor(App->renderer->renderer, 0, 0, 0, (Uint8)(normalized * 255.0F));
		SDL_RenderFillRect(App->renderer->renderer, NULL);

		if (moduleOff == nullptr && moduleOn != nullptr) {
			moduleOn->Enable();
			moduleOn = nullptr;
		}

		if (now >= totalTime) {
			if (fadingIn == true) {
				if (moduleOff != nullptr)
					moduleOff->Disable();
				moduleOn->Enable();

				totalTime += totalTime;
				startTime = SDL_GetTicks();
				fadingIn = false;
			}
			else {
				startTime = 0;
			}
		}
	}

	return UPDATE_CONTINUE;
}

void ModuleFadeToBlack::FadeToBlack(Module* module_on, Module* module_off, float time) {
	fadingIn = (module_off != nullptr) ? true : false;
	startTime = SDL_GetTicks();
	totalTime = (Uint32)(time  * 0.5F * 1000.0F);

	this->moduleOn = module_on;
	this->moduleOff = module_off;
}

bool ModuleFadeToBlack::isFading() const {
	return startTime > 0;
}
