#ifndef _MODULESCENEINTRO_H_
#define _MODULESCENEINTRO_H_

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
	unsigned int lastTime = 0;
	unsigned int currentTime = 0;
	GIF cinematic;
	GIF girl;
	GIF ghost;
	SDL_Texture *graphics = nullptr;
	SDL_Rect mainMenu;
	static bool hasPlayedIntro;
	static int counter;
};

#endif 