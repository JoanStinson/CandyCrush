#ifndef __MODULEAUDIO_H__
#define __MODULEAUDIO_H__

#include "Module.h"
#include <vector>

#define DEFAULT_MUSIC_FADE_TIME 2.0f

struct _Mix_Music;
struct Mix_Chunk;
typedef struct _Mix_Music Mix_Music;

class ModuleAudio : public Module {
public:
	ModuleAudio(bool start_enabled = true);
	~ModuleAudio();

	bool Init() override;
	bool CleanUp() override;

public:
	bool PlayMusic(const char *path, float fade_time = DEFAULT_MUSIC_FADE_TIME);
	unsigned int LoadFx(const char *path);
	bool PlayFx(unsigned int fx, int repeat = 0);

private:
	Mix_Music* music = nullptr;
	std::vector<Mix_Chunk*>	fx;
};

#endif // __MODULEAUDIO_H__