#include "Texture2D.h"

std::unordered_map<std::string, SDL_Texture*> Texture2D::m_TextureMap;

Texture2D::Texture2D()
{
	m_Tex = nullptr;
}

Texture2D::~Texture2D() {

	for (auto& texture : m_TextureMap) {
		if (texture.second) {
			SDL_DestroyTexture(texture.second);
			texture.second = nullptr;
			printf("texture in map ded\n");

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

	std::string base_path = SDL_GetBasePath();
	base_path.append("Images/" + filename);

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

void Texture2D::LoadClippedTexture(const std::string& filename, int srcx, int srcy, Vector2 _pos, int w, int h, float scale) {

	m_Tex = this->GetTexture(filename);

	m_SrcRect.x = srcx;
	m_SrcRect.y = srcy;

	m_DestRect.x = _pos.x;
	m_DestRect.y = _pos.y;

	m_SrcRect.w = m_DestRect.w = w;
	m_SrcRect.h = m_DestRect.h = h;

	m_DestRect.w *= scale;
	m_DestRect.h *= scale;

}

void Texture2D::KillTexture() {
	SDL_DestroyTexture(m_Tex);
	m_Tex = nullptr;
}

void Texture2D::RenderBackground() {
	SDL_RenderCopyF(Graphics::GetRenderer(), m_Tex, nullptr, &m_DestRect);
}

void Texture2D::RenderClippedTexture() {
	SDL_RenderCopyF(Graphics::GetRenderer(), m_Tex, &m_SrcRect, &m_DestRect);
}