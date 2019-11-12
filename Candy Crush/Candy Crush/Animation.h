#ifndef __ANIMATION_H__
#define __ANIMATION_H__

#include <vector>

class Animation {
public:
	Animation() : frames(), speed(1.0f), current_frame(0.0f) {}

	SDL_Rect& GetCurrentFrame() {
		current_frame += speed;
		if (current_frame >= frames.size())
			current_frame = 0.0f;
		return frames[(int)current_frame];
	}

	float GetCurrentFrameIndex() {
		return current_frame;
	}

	void ResetAnim() {
		current_frame = 0;
	}

public:
	float speed;
	std::vector<SDL_Rect> frames;

private:
	float current_frame;
};

#endif // __ANIMATION_H__