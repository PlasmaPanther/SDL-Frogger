#include "Font.h"

Font::Font() {
	if (TTF_Init() == -1) {
		printf("Font module could not start: %s\n", TTF_GetError());
	}

	m_FontSurface = nullptr;
	m_FontTexture = nullptr;
	m_Font = nullptr;
}

Font::~Font() {

	if (m_FontSurface) {
		SDL_FreeSurface(m_FontSurface);
		m_FontSurface = nullptr;
	}

	if (m_FontTexture) {
		SDL_DestroyTexture(m_FontTexture);
		m_FontTexture = nullptr;
	}

	if (m_Font) {
		TTF_CloseFont(m_Font);
		m_Font = nullptr;
	}

	TTF_Quit();
}

void Font::Load(const std::string& fontname, uint32_t size, std::string text, SDL_Color color) {

	std::string fontpath = "Resources/Fonts/" + fontname;

	if (!m_Font) {
		m_Font = TTF_OpenFont(fontpath.c_str(), size);
	}

	if (!m_FontSurface) {
		m_FontSurface = TTF_RenderText_Solid(m_Font, text.c_str(), color);
	}

	if (!m_FontTexture) {
		m_FontTexture = SDL_CreateTextureFromSurface(Graphics::GetRenderer(), m_FontSurface);
	}
}

void Font::LoadToText(const std::string& fontname, uint32_t size, int val, SDL_Color color) {

	std::string val_to_str = std::to_string(val);

	this->Load(fontname, size, val_to_str, color);

}

void Font::DrawText(int x, int y) {

	if (m_FontSurface) { //Prevents annoying segfault when switching between states
		m_DestRect.x = x;
		m_DestRect.y = y;
		m_DestRect.w = m_FontSurface->w;
		m_DestRect.h = m_FontSurface->h;

		SDL_RenderCopyF(Graphics::GetRenderer(), m_FontTexture, nullptr, &m_DestRect);
	}
}

void Font::ChangeText(const std::string& text, SDL_Color color) {

	SDL_DestroyTexture(m_FontTexture);
	m_FontTexture = nullptr;

	SDL_FreeSurface(m_FontSurface);
	m_FontSurface = nullptr;

	m_FontSurface = TTF_RenderText_Solid(m_Font, text.c_str(), color);
	m_FontTexture = SDL_CreateTextureFromSurface(Graphics::GetRenderer(), m_FontSurface);

}

void Font::ChangeToText(int val, SDL_Color color) {

	std::string val_to_str = std::to_string(val);
	this->ChangeText(val_to_str, color);

}

void Font::FreeFont() {

	TTF_CloseFont(m_Font);
	m_Font = nullptr;

	SDL_DestroyTexture(m_FontTexture);
	m_FontTexture = nullptr;

	SDL_FreeSurface(m_FontSurface);
	m_FontSurface = nullptr;

	printf("font freed\n");

}