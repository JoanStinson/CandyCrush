#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#pragma comment( lib, "SDL2_image/lib/x86/SDL2_image.lib" )
#pragma comment( lib, "SDL2_ttf/lib/x86/SDL2_ttf.lib" )
using namespace std;

ModuleTextures::ModuleTextures() {
}

// Destructor
ModuleTextures::~ModuleTextures() {
	IMG_Quit();
	TTF_Quit();
}

// Called before render is available
bool ModuleTextures::Init() {
	LOG("Init Image library");
	bool ret = true;

	// load support for the PNG image format
	int flags = IMG_INIT_PNG;
	int init = IMG_Init(flags);

	if ((init & flags) != flags) {
		LOG("Could not initialize Image lib. IMG_Init: %s", IMG_GetError());
		ret = false;
	}

	// Initialize SDL_ttf
	if (TTF_Init() == -1) {
		LOG("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
		ret = false;
	}

	return ret;
}

// Called before quitting
bool ModuleTextures::CleanUp() {
	LOG("Freeing textures and Image library");

	for (list<SDL_Texture*>::iterator it = textures.begin(); it != textures.end(); ++it)
		SDL_DestroyTexture(*it);

	textures.clear();
	return true;
}

// Load new texture from file path
SDL_Texture* const ModuleTextures::LoadImage(const char* path) {
	SDL_Texture* texture = nullptr;
	SDL_Surface* surface = IMG_Load(path);

	if (surface == nullptr) {
		LOG("Could not load surface with path: %s. IMG_Load: %s", path, IMG_GetError());
	}
	else {
		texture = SDL_CreateTextureFromSurface(App->renderer->renderer, surface);

		if (texture == nullptr) {
			LOG("Unable to create texture from surface! SDL Error: %s\n", SDL_GetError());
		}
		else {
			textures.push_back(texture);
		}

		SDL_FreeSurface(surface);
	}

	return texture;
}

// Free texture from memory
void ModuleTextures::Unload(SDL_Texture* texture) {
	for (list<SDL_Texture*>::iterator it = textures.begin(); it != textures.end(); ++it) {
		if (*it == texture) {
			SDL_DestroyTexture(*it);
			textures.erase(it);
			break;
		}
	}
}

SDL_Texture* const ModuleTextures::LoadText(const char *text, SDL_Color &textColor, int size, bool bold, const char *fontPath) {
	SDL_Texture* texture = nullptr;
	SDL_Surface* surface = nullptr;
	TTF_Font *font = TTF_OpenFont(fontPath, size);

	if (font == nullptr) {
		LOG("Could not load font with path: %s. TTF_Load: %s", fontPath, TTF_GetError());
	}
	else {
		if (bold) TTF_SetFontStyle(font, TTF_STYLE_BOLD);
		surface = TTF_RenderText_Solid(font, text, textColor);

		if (surface == nullptr) {
			LOG("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
		}
		else {
			texture = SDL_CreateTextureFromSurface(App->renderer->renderer, surface);

			if (texture == nullptr) {
				LOG("Unable to create texture from surface! SDL Error: %s\n", SDL_GetError());
			}
			else {
				textures.push_back(texture);
			}

			SDL_FreeSurface(surface);
		}
	}

	return texture;
}
