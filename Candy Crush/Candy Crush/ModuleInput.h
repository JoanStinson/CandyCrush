#ifndef __MODULEINPUT_H__
#define __MODULEINPUT_H__

#include "Module.h"
#include "Point.h"
#include <SDL_scancode.h>

#define NUM_MOUSE_BUTTONS 5

typedef enum EventWindow {
	WE_QUIT = 0,
	WE_HIDE = 1,
	WE_SHOW = 2,
	WE_COUNT
};

typedef enum KeyState {
	KEY_IDLE = 0,
	KEY_DOWN,
	KEY_REPEAT,
	KEY_UP
};

typedef enum MouseMove {
	RIGHT,
	LEFT,
	UP,
	DOWN
};

class ModuleInput : public Module {
public:
	ModuleInput();
	~ModuleInput();

	bool Init() override;
	bool Start() override;
	update_status PreUpdate() override;
	bool CleanUp() override;

public:
	KeyState GetKey(int id) const;
	KeyState GetMouseButtonDown(int id) const; 
	bool GetWindowEvent(EventWindow code) const;
	const iPoint& GetMouseMotion() const;
	const iPoint& GetMousePosition() const;

private:
	bool windowEvents[WE_COUNT];
	KeyState* keyboard = nullptr;
	KeyState mouseButtons[NUM_MOUSE_BUTTONS];
	iPoint mouseMotion;
	iPoint mouse;
};

#endif // __MODULEINPUT_H__