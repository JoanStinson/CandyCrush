#ifndef __MODULERENDER_H__
#define __MODULERENDER_H__

#include "Module.h"
#include "Globals.h"

struct SDL_Texture;
struct SDL_Renderer;
struct SDL_Rect;

class ModuleRender : public Module {
public:
	ModuleRender();
	~ModuleRender();

	bool Init() override;
	update_status PreUpdate() override;
	update_status Update() override;
	update_status PostUpdate() override;
	bool CleanUp() override;

	bool Blit(SDL_Texture* texture, int x, int y, SDL_Rect* section, float speed = 1.0f);
	void ResetCamera();

public:
	SDL_Renderer* renderer = nullptr;
	SDL_Rect camera;
};

#endif // __MODULERENDER_H__