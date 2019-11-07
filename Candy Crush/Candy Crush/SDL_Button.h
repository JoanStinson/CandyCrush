// SDL_button.h - interface for a button type compatible with SDL
// Author : Tim Smith (tim14smith@gmail.com)

#include <SDL.h>
#include <stdbool.h>

// Representation of a button as a surface with a rectangle defining its location and size
typedef struct {
	SDL_Surface *internal_surface;
	SDL_Rect *location_and_size;
} SDL_Button_t;

// Get a new SDL button
SDL_Button_t* SDL_Button(SDL_Surface *surface, int x_location, int y_location, int button_width, int button_h);

// Free a button and its members
void SDL_Button_free(SDL_Button_t *button);

// Returns true if the left mouse button is pressed on the button
bool SDL_Button_mouse_down(SDL_Button_t *button, SDL_Event *e);

// Returns true if the left mouse button is released on the button
bool SDL_Button_mouse_up(SDL_Button_t *button, SDL_Event *e);

// Returns true if the mouse cursor is over the button
bool SDL_Button_mouse_over(SDL_Button_t *button, SDL_Event *e);

// Returns the opposite of SDL_Button_mouse_over
bool SDL_Button_mouse_out(SDL_Button_t *button, SDL_Event *e);

bool mouse_on_button(SDL_Rect *button_rect, int mouse_x, int mouse_y);