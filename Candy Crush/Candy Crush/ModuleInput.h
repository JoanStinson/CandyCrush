#ifndef _MODULEINPUT_H_
#define _MODULEINPUT_H_
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

typedef enum class MouseMove {
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

	KeyState GetKey(int id) const {
		return keyboard[id];
	}

	KeyState GetMouseButtonDown(int id) const {
		return mouse_buttons[id - 1];
	}

	bool GetWindowEvent(EventWindow code) const;

	const iPoint& GetMouseMotion() const;
	const iPoint& GetMousePosition() const;

private:
	bool windowEvents[WE_COUNT];
	KeyState* keyboard;
	KeyState mouse_buttons[NUM_MOUSE_BUTTONS];
	iPoint mouse_motion;
	iPoint mouse;
};

#endif 