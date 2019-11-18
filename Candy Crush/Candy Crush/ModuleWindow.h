#ifndef __MODULEWINDOW_H__
#define __MODULEWINDOW_H__

#include "Module.h"

struct SDL_Window;
struct SDL_Surface;

class ModuleWindow : public Module {
public:
	ModuleWindow();
	~ModuleWindow();

	bool Init() override;
	bool CleanUp() override;

public:
	SDL_Window& GetWindow() const;

private:
	SDL_Window* window = nullptr;
	SDL_Surface* screenSurface = nullptr;
};

#endif // __MODULEWINDOW_H__