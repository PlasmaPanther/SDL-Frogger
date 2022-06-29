#pragma once
#include <SDL_mixer.h>
#include <unordered_map>

class AudioPlayer
{
public:
	AudioPlayer();
	~AudioPlayer();

	void PlayMusic(std::string filename, int loops);
	void PauseMusic();
	void ResumeMusic();

	void PlaySFX(std::string filename, int loops, int channel);

private:
	Mix_Music* GetMusic(std::string filename);
	Mix_Chunk* GetSFX(std::string filename);

	std::unordered_map<std::string, Mix_Music*> m_MusicMap;
	std::unordered_map<std::string, Mix_Chunk*> m_SFXMap;

};

