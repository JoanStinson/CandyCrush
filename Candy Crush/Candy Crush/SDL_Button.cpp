// SDL_button.c - an implementation of buttons to be used with SDL
// Author : Tim Smith (tim14smith@gmail.com)

#include "SDL_Button.h"
#include <stdbool.h>

void SDL_Button_free(SDL_Button_t *button) {
	delete button->internal_surface;
	delete button->location_and_size;
	delete button;
}

// Get a new SDL button
SDL_Button_t* SDL_Button(SDL_Surface *surface, int x_location, int y_location, int button_width, int button_height) {
	SDL_Button_t *button = new SDL_Button_t();
	button->internal_surface = surface;

	SDL_Rect *rect = new SDL_Rect();
	rect->x = x_location;
	rect->y = y_location;
	rect->w = button_width;
	rect->h = button_height;
	button->location_and_size = rect;

	return button;
}

bool mouse_on_button(SDL_Rect *button_rect, int mouse_x, int mouse_y) {
	int button_x = button_rect->x;
	int button_y = button_rect->y;
	int button_w = button_rect->w;
	int button_h = button_rect->h;
	bool in_width = (mouse_x > button_x) && (mouse_x < (button_x + button_w));
	bool in_height = (mouse_y > button_y) && (mouse_y < (button_y + button_h));
	return (in_width && in_height);
}

bool SDL_Button_mouse_down(SDL_Button_t *button, SDL_Event *e) {
	if ((e->type == SDL_MOUSEBUTTONDOWN)) {
		int x = e->button.x;
		int y = e->button.y;
		return (mouse_on_button(button->location_and_size, x, y));
	}
	return false;
}

bool SDL_Button_mouse_up(SDL_Button_t *button, SDL_Event *e) {
	if ((e->type == SDL_MOUSEBUTTONUP)) {
		int x = e->button.x;
		int y = e->button.y;
		return (mouse_on_button(button->location_and_size, x, y));
	}
	return false;

}

bool SDL_Button_mouse_over(SDL_Button_t *button, SDL_Event *e) {
	if (e->type == SDL_MOUSEMOTION) {
		int x = e->motion.x;
		int y = e->motion.y;
		return(mouse_on_button(button->location_and_size, x, y));
	}
	return false;
}

bool SDL_Button_mouse_out(SDL_Button_t *button, SDL_Event *e) {
	return !SDL_Button_mouse_over(button, e);
}