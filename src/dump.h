#pragma once
//Header used for code which i dont want to delete and might re-use later

/*Font::~Font() {

	for (auto& font : m_FontMap) {
		if (font.second) {
			TTF_CloseFont(font.second);
			font.second = nullptr;
			printf("font in map ded\n");
		}
	}

	m_FontMap.clear();

	for (auto& tex : m_fontTexture_vector) {

		if (!m_fontTexture_vector.empty())
		{
			SDL_DestroyTexture(tex);
			tex = nullptr;

			SDL_DestroyTexture(text_font); //i don't know if this works but im hoping it frees all the loaded font textures passed to the member var
			text_font = nullptr;

			printf("Texture in vector ded\n");
		}
	}

	m_fontTexture_vector.clear();
	m_fontTexture_vector.shrink_to_fit(); //set size to 0

	TTF_Quit();
}*/

/*TTF_Font* Font::GetFont(std::string& fontname, int size) {
	std::string fontpath = SDL_GetBasePath();
	fontpath.append("Fonts/" + fontname);

	TTF_Font* font = nullptr;

	if (m_FontMap[fontpath] == nullptr) {
		m_FontMap[fontpath] = font = TTF_OpenFont(fontpath.c_str(), size);

		if (m_FontMap[fontpath] == nullptr) {
			printf("font did not load %s\n", TTF_GetError());
		}
	}

	return m_FontMap[fontpath];
}

SDL_Texture* Font::LoadFontTexture(SDL_Surface* surf) {

	//making this a const ptr doesnt work
	SDL_Texture* const t = SDL_CreateTextureFromSurface(Graphics::GetRenderer(), surf); //this is where the leak is coming from

	m_fontTexture_vector.push_back(t); //inserts the loaded texture

	return m_fontTexture_vector.back(); //returns the last loaded texture
}

void Font::LoadFont(std::string name, std::string text, Vector2 _pos, int width, int height, int size, SDL_Color color) {
	SDL_Texture* tex = nullptr;

	SDL_Surface* textsurface = nullptr;
	textsurface = TTF_RenderText_Solid(this->GetFont(name, size), text.c_str(), color);

	if (textsurface == nullptr) {
		printf("surface didnt load %s\n", TTF_GetError());
	}

	//text_font = LoadFontTexture(textsurface); //SDL_CreateTextureFromSurface creates a memory leak
	tex = SDL_CreateTextureFromSurface(Graphics::GetRenderer(), textsurface);

	SDL_FreeSurface(textsurface);
	textsurface = nullptr;

	if (text_font == nullptr) {
		printf("text texture not created %s\n", SDL_GetError());
	}

	object_rect.x = _pos.x;
	object_rect.y = _pos.y;

	object_rect.w = width;
	object_rect.h = height;

	SDL_RenderCopy(Graphics::GetRenderer(), tex, nullptr, &object_rect);
}*/