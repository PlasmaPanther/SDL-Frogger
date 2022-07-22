#pragma once
#include "Texture2D.h"

class AnimatedTexture2D: public Texture2D
{
public:

	AnimatedTexture2D();
	~AnimatedTexture2D();

	void LoadAnimation(const std::string& filename, Vector2 _pos, int w, int h, int rotation, Vector2 _scale);
	void RenderAnimation(int SourceX, int SourceY, uint32_t speed, int numframes, int framenuminsheet, SDL_RendererFlip flip = SDL_RendererFlip::SDL_FLIP_NONE, bool renderFlag = true);

	void LoadEx(const std::string& filename, Vector2 _pos);
	void RenderEx(int speed, int totalframes);

	uint8_t GetCurrentFrame() const;

private:

	SDL_Texture* m_Animatedtex;

	int m_Rotation;

	uint8_t m_currentFrame;
};

