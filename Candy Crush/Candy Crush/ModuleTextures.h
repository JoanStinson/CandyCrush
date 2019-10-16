#ifndef __MODULETEXTURES_H__
#define __MODULETEXTURES_H__

#include <list>
#include "Module.h"
#include "Globals.h"

struct SDL_Texture;

class ModuleTextures : public Module {
public:
	ModuleTextures();
	~ModuleTextures();

	bool Init() override;
	bool CleanUp() override;

	SDL_Texture* const LoadImage(const char* path);
	SDL_Texture* const LoadText(const char *text, SDL_Color &textColor, int size = 10, bool bold = true, const char *fontPath = "Game/RobotoSlab-Thin.ttf");
	void Unload(SDL_Texture* texture);

private:
	std::list<SDL_Texture*> textures;
};

#endif // __MODULETEXTURES_H__