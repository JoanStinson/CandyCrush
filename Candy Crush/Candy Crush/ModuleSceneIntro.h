#ifndef __MODULESCENEINTRO_H__
#define __MODULESCENEINTRO_H__

#include "Module.h"
#include "Animation.h"

struct SDL_Texture;
typedef struct CEV_GifAnim CEV_GifAnim;

struct GIF {
	CEV_GifAnim *anim = nullptr;
	SDL_Texture *texture = nullptr;
};

class ModuleSceneIntro : public Module {
public:
	ModuleSceneIntro(bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start() override;
	update_status Update() override;
	bool CleanUp() override;

private:
	GIF cinematic;
	GIF girl;
	GIF ghost;
	SDL_Texture* graphics = nullptr;
	SDL_Rect mainMenu;

	unsigned int lastTime = 0;
	unsigned int currentTime = 0;
	static bool hasPlayedIntro;
	static int counter;
	unsigned int clickButtonSFX;
};

#endif // __MODULESCENEINTRO_H__