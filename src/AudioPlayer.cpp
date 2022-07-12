#include "AudioPlayer.h"
#include <SDL.h>

AudioPlayer::AudioPlayer() {

	if (SDL_Init(SDL_INIT_AUDIO) != 0) {
		printf("Audio could not initialize %s\n", SDL_GetError());
	}

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) < 0) {
		printf("Mixer could not initialize %s\n", Mix_GetError());
	}
}

AudioPlayer::~AudioPlayer() {

	for (auto& music : m_MusicMap) {
		if (music.second) {
			Mix_FreeMusic(music.second);
			music.second = nullptr;
			printf("Music ded\n");
		}
	}
	m_MusicMap.clear();
	

	for (auto& sfx : m_SFXMap) {
		if (sfx.second) {
			Mix_FreeChunk(sfx.second);
			sfx.second = nullptr;
			printf("sfx ded\n");
		}
	}
	m_SFXMap.clear();

	Mix_Quit();
}

Mix_Music* AudioPlayer::GetMusic(std::string filename) {
	std::string basepath = SDL_GetBasePath();
	basepath.append("Resources/Audio/" + filename);

	if (m_MusicMap[basepath] == nullptr) {
		m_MusicMap[basepath] = Mix_LoadMUS(basepath.c_str());

		if (m_MusicMap[basepath] == nullptr) {
			printf("Could not load file %s\n", Mix_GetError());
		}
	}

	return m_MusicMap[basepath];
}

Mix_Chunk* AudioPlayer::GetSFX(std::string filename) {
	std::string basepath = SDL_GetBasePath();
	basepath.append("Sounds/" + filename);

	if (m_SFXMap[basepath] == nullptr) {
		m_SFXMap[basepath] = Mix_LoadWAV(basepath.c_str());

		if (m_SFXMap[basepath] == nullptr) {
			printf("Could not load file %s\n", Mix_GetError());
		}
	}

	return m_SFXMap[basepath];
}

void AudioPlayer::PlayMusic(std::string file, int loops)
{
	Mix_PlayMusic(this->GetMusic(file), loops);
}

void AudioPlayer::PauseMusic() {
	if (Mix_PlayingMusic != 0) {
		Mix_PauseMusic();
	}
}

void AudioPlayer::ResumeMusic() {
	if (Mix_PausedMusic() != 0) {
		Mix_ResumeMusic();
	}
}

void AudioPlayer::PlaySFX(std::string file, int loops, int channel)
{
	Mix_PlayChannel(channel, this->GetSFX(file), loops);
}