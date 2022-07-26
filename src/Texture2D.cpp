#include "Texture2D.h"
#include <iostream>

Texture2D::Texture2D()
{
	m_Tex = nullptr;
}

Texture2D::~Texture2D() {

	for (auto& texture : m_TextureMap) {
		if (texture.second) {
			SDL_DestroyTexture(texture.second);
			texture.second = nullptr;
			std::cout << "Texture Freed!" << std::endl;

		}
	}
	m_TextureMap.clear();

	if (m_Tex) {
		SDL_DestroyTexture(m_Tex);
		m_Tex = nullptr;
	}
}

SDL_Texture* Texture2D::GetTexture(const std::string& filename)
{

	std::string base_path = "";
	base_path.append("Resources/Textures/" + filename);

	if (m_TextureMap[base_path] == nullptr) {
		m_TextureMap[base_path] = IMG_LoadTexture(Graphics::GetRenderer(), base_path.c_str());

		if (m_TextureMap[base_path] == nullptr) {
			printf("Texture could not be created %s\n", IMG_GetError());
		}
	}
	
	return m_TextureMap[base_path];
}

void Texture2D::LoadBackground(const std::string& filename)
{
	m_Tex = GetTexture(filename);

	m_DestRect.x = 0;
	m_DestRect.y = 0;

	m_DestRect.w = 800;
	m_DestRect.h = 600;

}

void Texture2D::LoadClippedTexture(const std::string& filename, int srcx, int srcy, Vector2 _pos, int w, int h, Vector2 scale) {

	m_Tex = this->GetTexture(filename);

	m_SrcRect.x = srcx;
	m_SrcRect.y = srcy;

	m_DestRect.x = _pos.x;
	m_DestRect.y = _pos.y;

	m_SrcRect.w = m_DestRect.w = w;
	m_SrcRect.h = m_DestRect.h = h;

	m_DestRect.w *= scale.x;
	m_DestRect.h *= scale.y;

}

void Texture2D::KillTexture() {
	SDL_DestroyTexture(m_Tex);
	m_Tex = nullptr;
}

void Texture2D::RenderBackground(bool renderFlag) {

	if (renderFlag) {
		SDL_RenderCopyF(Graphics::GetRenderer(), m_Tex, nullptr, &m_DestRect);
	}
}

void Texture2D::RenderClippedTexture(float angle, bool renderFlag) {

	if (renderFlag) {
		SDL_RenderCopyExF(Graphics::GetRenderer(), m_Tex, &m_SrcRect, &m_DestRect, angle, nullptr, SDL_FLIP_NONE);
	}
}