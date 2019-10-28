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

typedef enum class MouseMove {
	RIGHT,
	LEFT,
	UP,
	DOWN
};

class ModuleInput : public Module {

public:

	ModuleInput();

	// Destructor
	~ModuleInput();

	// Called before render is available
	bool Init() override;

	// Called before the first frame
	bool Start() override;

	// Called each loop iteration
	update_status PreUpdate() override;

	// Called before quitting
	bool CleanUp() override;

	// Check key states (includes mouse and joy buttons)
	KeyState GetKey(int id) const {
		return keyboard[id];
	}

	KeyState GetMouseButtonDown(int id) const {
		return mouse_buttons[id - 1];
	}

	// Check for window events last frame
	bool GetWindowEvent(EventWindow code) const;

	// Get mouse / axis position
	const iPoint& GetMouseMotion() const;
	const iPoint& GetMousePosition() const;

private:
	bool		windowEvents[WE_COUNT];
	KeyState*	keyboard;
	KeyState	mouse_buttons[NUM_MOUSE_BUTTONS];
	iPoint mouse_motion;
	iPoint mouse;
};

#endif // __MODULEINPUT_H__