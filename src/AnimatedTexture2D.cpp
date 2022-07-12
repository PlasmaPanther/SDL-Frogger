#include "AnimatedTexture2D.h"

AnimatedTexture2D::AnimatedTexture2D()
{
	m_Animatedtex = nullptr;
	m_currentFrame = 0;
	m_Rotation = 0;
}

AnimatedTexture2D::~AnimatedTexture2D()
{
	if (m_Animatedtex) {
		SDL_DestroyTexture(m_Animatedtex);
		m_Animatedtex = nullptr;
	}
}

void AnimatedTexture2D::LoadAnimation(const std::string& filename, Vector2 _pos, int w, int h, int rotation, Vector2 scale)
{
	m_Animatedtex = GetTexture(filename);

	m_DestRect.x = _pos.x;
	m_DestRect.y = _pos.y;

	m_SrcRect.w = m_DestRect.w = w;
	m_SrcRect.h = m_DestRect.h = h;

	m_DestRect.w *= scale.x;
	m_DestRect.h *= scale.y;

	m_Rotation = rotation;
}

void AnimatedTexture2D::RenderAnimation(int SourceX, int SourceY, uint32_t speed, int numframes, int framenuminsheet, bool renderFlag, SDL_RendererFlip flip) {

	m_currentFrame = static_cast<int>(((SDL_GetTicks() / speed) % numframes));

	m_SrcRect.x = SourceX * (m_currentFrame + framenuminsheet);
	m_SrcRect.y = SourceY;

	if (renderFlag) {
		SDL_RenderCopyExF(Graphics::GetRenderer(), m_Animatedtex, &m_SrcRect, &m_DestRect, m_Rotation, nullptr, flip);
	}
}

void AnimatedTexture2D::LoadEx(const std::string& filename, Vector2 _pos)
{
	m_Animatedtex = GetTexture(filename);

	m_SrcRect.x = 0;

	SDL_QueryTexture(m_Animatedtex, nullptr, nullptr, &m_SrcRect.w, &m_SrcRect.h);

	m_DestRect.x = _pos.x;
	m_DestRect.y = _pos.y;

	m_DestRect.w = 140;
	m_DestRect.h = 200;

	m_SrcRect.w = 75;
	m_SrcRect.y = 0;
	//m_SrcRect.h = 25;
}

void AnimatedTexture2D::RenderEx(int speed, int totalframes)
{
	m_currentFrame = static_cast<int>((SDL_GetTicks() / speed) % totalframes);

	m_SrcRect.x = m_currentFrame * m_SrcRect.w;

	SDL_RenderCopyExF(Graphics::GetRenderer(), m_Animatedtex, &m_SrcRect, &m_DestRect, m_Rotation, nullptr, SDL_FLIP_NONE);
}

uint8_t AnimatedTexture2D::GetCurrentFrame() const
{
	return m_currentFrame;
}
