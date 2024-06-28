#pragma once

#include "SDL_mixer.h"

#include <vector>
#include <string>

enum {
	CH_ANY = -1,
	CH_DINO,
};

enum {
	SND_DINO_JUMP,
	SND_DINO_LAND,
	SND_COLLISION,
};

enum {
	MORNING_MUSIC,
	NOON_MUSIC,
	NIGHT_MUSIC,
};

class SoundManager {
	const int mChannelsCount = 8;
	const int mSoundsCount = 3;
	const int mMusicCount = 3;

	int mCurrentPlayingMusic;

	std::vector<Mix_Chunk*> mSounds;
	std::vector<Mix_Music*> mMusic;

public:
	~SoundManager();

	void init();
	void playSound(int id, int channel);
	void playMusic(int id);

	int getCurrentPlayingMusic() const;
};