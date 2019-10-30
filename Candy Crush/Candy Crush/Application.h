#ifndef _APPLICATION_H_
#define _APPLICATION_H_
#include "Module.h"
#include <list>

class ModuleRender;
class ModuleWindow;
class ModuleTextures;
class ModuleInput;
class ModuleAudio;
class ModuleFadeToBlack;
class ModulePlayer;
class ModuleSceneIntro;
class ModuleSceneGame;

class Application {
public:
	ModuleRender *renderer = nullptr;
	ModuleWindow *window = nullptr;
	ModuleTextures *textures = nullptr;
	ModuleInput *input = nullptr;
	ModuleAudio *audio = nullptr;
	ModuleFadeToBlack *fade = nullptr;
	ModulePlayer *player = nullptr;
	ModuleSceneIntro *sceneIntro = nullptr;
	ModuleSceneGame *sceneGame = nullptr;

public:
	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();

private:
	std::list<Module*> modules;
};

extern Application* App;

#endif 