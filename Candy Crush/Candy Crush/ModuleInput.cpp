#include "ModuleInput.h"
#include "Application.h"
#include <SDL.h>

#define MAX_KEYS 300

ModuleInput::ModuleInput() : Module(), mouseMotion({ 0,0 }), mouse({ 0, 0 }) {
	keyboard = new KeyState[MAX_KEYS];
	memset(keyboard, KEY_IDLE, sizeof(KeyState) * MAX_KEYS);
	memset(mouseButtons, KEY_IDLE, sizeof(KeyState) * NUM_MOUSE_BUTTONS);
}

ModuleInput::~ModuleInput() {
	RELEASE_ARRAY(keyboard);
}

bool ModuleInput::Init() {
	LOG("Init SDL input event system");
	bool ret = true;
	SDL_Init(0);

	if (SDL_InitSubSystem(SDL_INIT_EVENTS) < 0) {
		LOG("SDL_EVENTS could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

	return ret;
}

bool ModuleInput::Start() {
	return true;
}

update_status ModuleInput::PreUpdate() {
	static SDL_Event event;

	mouseMotion = { 0, 0 };
	memset(windowEvents, false, WE_COUNT * sizeof(bool));

	const Uint8* keys = SDL_GetKeyboardState(NULL);

	for (int i = 0; i < MAX_KEYS; ++i) {
		if (keys[i] == 1) {
			if (keyboard[i] == KEY_IDLE)
				keyboard[i] = KEY_DOWN;
			else
				keyboard[i] = KEY_REPEAT;
		}
		else {
			if (keyboard[i] == KEY_REPEAT || keyboard[i] == KEY_DOWN)
				keyboard[i] = KEY_UP;
			else
				keyboard[i] = KEY_IDLE;
		}
	}

	for (int i = 0; i < NUM_MOUSE_BUTTONS; ++i) {
		if (mouseButtons[i] == KEY_DOWN)
			mouseButtons[i] = KEY_REPEAT;

		if (mouseButtons[i] == KEY_UP)
			mouseButtons[i] = KEY_IDLE;
	}

	while (SDL_PollEvent(&event) != 0) {
		switch (event.type) {
		case SDL_QUIT:
			windowEvents[WE_QUIT] = true;
			break;

		case SDL_WINDOWEVENT:
			switch (event.window.event) {
			case SDL_WINDOWEVENT_LEAVE:
			case SDL_WINDOWEVENT_HIDDEN:
			case SDL_WINDOWEVENT_MINIMIZED:
			case SDL_WINDOWEVENT_FOCUS_LOST:
				windowEvents[WE_HIDE] = true;
				break;

			case SDL_WINDOWEVENT_ENTER:
			case SDL_WINDOWEVENT_SHOWN:
			case SDL_WINDOWEVENT_FOCUS_GAINED:
			case SDL_WINDOWEVENT_MAXIMIZED:
			case SDL_WINDOWEVENT_RESTORED:
				windowEvents[WE_SHOW] = true;
				break;
			}
			break;

		case SDL_MOUSEBUTTONDOWN:
			mouseButtons[event.button.button - 1] = KEY_DOWN;
			break;

		case SDL_MOUSEBUTTONUP:
			mouseButtons[event.button.button - 1] = KEY_UP;
			break;

		case SDL_MOUSEMOTION:
			mouseMotion.x = event.motion.xrel / SCREEN_SIZE;
			mouseMotion.y = event.motion.yrel / SCREEN_SIZE;
			mouse.x = event.motion.x / SCREEN_SIZE;
			mouse.y = event.motion.y / SCREEN_SIZE;
			break;
		}
	}

	if (GetWindowEvent(EventWindow::WE_QUIT) == true || GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		return UPDATE_STOP;

	return UPDATE_CONTINUE;
}

bool ModuleInput::CleanUp() {
	LOG("Quitting SDL event subsystem");
	SDL_QuitSubSystem(SDL_INIT_EVENTS);
	return true;
}

KeyState ModuleInput::GetKey(int id) const {
	return keyboard[id];
}

KeyState ModuleInput::GetMouseButtonDown(int id) const {
	return mouseButtons[id - 1];
}

bool ModuleInput::GetWindowEvent(EventWindow ev) const {
	return windowEvents[ev];
}

const iPoint& ModuleInput::GetMousePosition() const {
	return mouse;
}

const iPoint& ModuleInput::GetMouseMotion() const {
	return mouseMotion;
}
