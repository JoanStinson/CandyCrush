#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Module.h"
#include <list>

class ModuleRender;
class ModuleWindow;
class ModuleTextures;
class ModuleInput;
class ModuleAudio;
class ModuleFadeToBlack;
class ModuleSceneIntro;
class ModuleSceneGame;

class Application {
public:
	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();

public:
	ModuleRender* renderer = nullptr;
	ModuleWindow* window = nullptr;
	ModuleTextures* textures = nullptr;
	ModuleInput* input = nullptr;
	ModuleAudio* audio = nullptr;
	ModuleFadeToBlack* fade = nullptr;
	ModuleSceneIntro* sceneIntro = nullptr;
	ModuleSceneGame* sceneGame = nullptr;

private:
	std::list<Module*> modules;
};

extern Application* App;

#endif // __APPLICATION_H__