#include "SoundManager.h"

SoundManager::~SoundManager() {
	for (auto& sound : mSounds) {
		if (sound != nullptr) {
			Mix_FreeChunk(sound);
		}
	}

	for (auto& music : mMusic) {
		if (music != nullptr) {
			Mix_HaltMusic();
			Mix_FreeMusic(music);
		}
	}
}

void SoundManager::init() {
	Mix_AllocateChannels(mChannelsCount);

	mSounds.resize(mSoundsCount);
	mMusic.resize(mMusicCount);

	mSounds[SND_DINO_JUMP] = Mix_LoadWAV("assets\\sounds\\mixkit-player-jumping-in-a-video-game-2043.wav");
	mSounds[SND_DINO_LAND] = Mix_LoadWAV("assets\\sounds\\161237-Snow-Impact-Gritty-Thump.wav");
	mSounds[SND_COLLISION] = Mix_LoadWAV("assets\\sounds\\mixkit-short-buzzer-sound-2963.wav");

	mMusic[MORNING_MUSIC] = Mix_LoadMUS("assets\\sounds\\mixkit-insects-birds-and-frogs-in-the-swamp-ambience-40.wav");
	mMusic[NOON_MUSIC] = Mix_LoadMUS("assets\\sounds\\mixkit-river-atmosphere-in-a-forest-2450.wav");
	mMusic[NIGHT_MUSIC] = Mix_LoadMUS("assets\\sounds\\mixkit-night-crickets-near-the-swamp-1782.wav");
}

void SoundManager::playSound(int id, int channel) {
	int loops = 0;
	
	Mix_PlayChannel(channel, mSounds[id], loops);
}

int SoundManager::getCurrentPlayingMusic() const {
	return mCurrentPlayingMusic;
}

void SoundManager::playMusic(int id) {
	Mix_PlayMusic(mMusic[id], -1);

	mCurrentPlayingMusic = id;
}
