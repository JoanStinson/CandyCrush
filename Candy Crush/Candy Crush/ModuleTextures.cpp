#include "ModuleTextures.h"
#include "Application.h"
#include "ModuleRender.h"

ModuleTextures::ModuleTextures() {
}

ModuleTextures::~ModuleTextures() {
	IMG_Quit();
	TTF_Quit();
}

bool ModuleTextures::Init() {
	LOG("Init Image library");
	bool ret = true;

	// Load support for the PNG image format
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

bool ModuleTextures::CleanUp() {
	LOG("Freeing textures and Image library");

	for (std::list<SDL_Texture*>::iterator it = textures.begin(); it != textures.end(); ++it)
		SDL_DestroyTexture(*it);

	textures.clear();
	return true;
}

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

SDL_Texture* const ModuleTextures::LoadText(const char *text, int size, SDL_Color &textColor, bool bold, const char *fontPath) {
	SDL_Texture* texture = nullptr;
	SDL_Surface* surface = nullptr;
	TTF_Font *font = TTF_OpenFont(fontPath, size);

	if (font == nullptr) {
		LOG("Could not load font with path: %s. TTF_Load: %s", fontPath, TTF_GetError());
	}
	else {
		if (bold) TTF_SetFontStyle(font, TTF_STYLE_BOLD);
		surface = TTF_RenderText_Blended(font, text, textColor);

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

void ModuleTextures::Unload(SDL_Texture* texture) {
	for (std::list<SDL_Texture*>::iterator it = textures.begin(); it != textures.end(); ++it) {
		if (*it == texture) {
			SDL_DestroyTexture(*it);
			textures.erase(it);
			break;
		}
	}
}
