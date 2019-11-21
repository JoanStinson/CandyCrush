#include "ModuleAudio.h"
#include "Application.h"
#include <SDL.h>
#include <SDL_mixer.h>

ModuleAudio::ModuleAudio(bool start_enabled) : Module(start_enabled) {
}

ModuleAudio::~ModuleAudio() {
}

bool ModuleAudio::Init() {
	LOG("Loading Audio Mixer");
	bool ret = true;
	SDL_Init(0);

	if (SDL_InitSubSystem(SDL_INIT_AUDIO) < 0) {
		LOG("SDL_INIT_AUDIO could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

	// Load support for the OGG format
	int flags = MIX_INIT_OGG;
	int init = Mix_Init(flags);

	if ((init & flags) != flags) {
		LOG("Could not initialize Mixer lib. Mix_Init: %s", Mix_GetError());
		ret = false;
	}

	// Initialize SDL_mixer
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
		LOG("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
		ret = false;
	}

	return ret;
}

bool ModuleAudio::CleanUp() {
	LOG("Freeing sound FX, closing Mixer and Audio subsystem");

	if (music != nullptr) {
		Mix_FreeMusic(music);
	}

	for (std::vector<Mix_Chunk*>::iterator it = fx.begin(); it != fx.end(); ++it)
		Mix_FreeChunk(*it);

	fx.clear();
	Mix_CloseAudio();
	Mix_Quit();
	SDL_QuitSubSystem(SDL_INIT_AUDIO);
	return true;
}

bool ModuleAudio::PlayMusic(const char* path, float fade_time) {
	bool ret = true;

	if (music != nullptr) {
		if (fade_time > 0.0F) {
			Mix_FadeOutMusic((int)(fade_time * 1000.0F));
		}
		else {
			Mix_HaltMusic();
		}

		// this call blocks until fade out is done
		Mix_FreeMusic(music);
	}

	music = Mix_LoadMUS(path);

	if (music == nullptr) {
		LOG("Cannot load music %s. Mix_GetError(): %s\n", path, Mix_GetError());
		ret = false;
	}
	else {
		if (fade_time > 0.0F) {
			if (Mix_FadeInMusic(music, -1, (int)(fade_time * 1000.0F)) < 0) {
				LOG("Cannot fade in music %s. Mix_GetError(): %s", path, Mix_GetError());
				ret = false;
			}
		}
		else {
			if (Mix_PlayMusic(music, -1) < 0) {
				LOG("Cannot play in music %s. Mix_GetError(): %s", path, Mix_GetError());
				ret = false;
			}
		}
	}

	LOG("Successfully playing %s", path);
	return ret;
}

void ModuleAudio::PauseMusic() {
	Mix_PauseMusic();
}

void ModuleAudio::ResumeMusic() {
	Mix_ResumeMusic();
}

void ModuleAudio::StopMusic() {
	Mix_HaltMusic();
}

unsigned int ModuleAudio::LoadFx(const char* path) {
	unsigned int ret = 0;
	Mix_Chunk* chunk = Mix_LoadWAV(path);

	if (chunk == nullptr) {
		LOG("Cannot load wav %s. Mix_GetError(): %s", path, Mix_GetError());
	}
	else {
		fx.push_back(chunk);
		ret = fx.size() - 1;
	}

	return ret;
}

bool ModuleAudio::PlayFx(unsigned int id, int repeat) {
	bool ret = false;

	if (id < fx.size()) {
		Mix_PlayChannel(-1, fx[id], repeat);
		ret = true;
	}

	return ret;
}
