#pragma once
#include "Object2D.h"
#include <map>
#include <string>

class Texture2D: public Object2D
{
public:
	Texture2D();
	virtual ~Texture2D();
	
	void LoadBackground(const std::string& filename);
	void LoadClippedTexture(const std::string& filename, int srcX, int srcY, Vector2 _pos, int w, int h, float scale);

	void RenderBackground();
	void RenderClippedTexture(bool renderFlag = true);

	void KillTexture();

	void SwitchTexture(SDL_Texture* tex) { m_Tex = tex; }
	SDL_Texture* GetTex() { return m_Tex; }

private:

	static inline std::map<std::string, SDL_Texture*>m_TextureMap;

	SDL_Texture* m_Tex;

protected:

	SDL_Texture* GetTexture(const std::string& filename);

};