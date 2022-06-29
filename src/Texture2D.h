#pragma once
#include "Object2D.h"
#include <unordered_map>

class Texture2D: public Object2D
{
public:
	Texture2D();
	virtual ~Texture2D();
	
	void LoadBackground(const std::string& filename);
	void LoadClippedTexture(const std::string& filename, int srcX, int srcY, Vector2 _pos, int w, int h, float scale);

	void RenderBackground();
	void RenderClippedTexture();

	void KillTexture();

private:

	static std::unordered_map<std::string, SDL_Texture*>m_TextureMap;

	SDL_Texture* m_Tex;

protected:

	SDL_Texture* GetTexture(const std::string& filename);

};