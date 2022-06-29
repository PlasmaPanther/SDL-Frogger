#pragma once
#include <SDL.h>

namespace TileProperties {
	constexpr int TOTAL_TILES = 96;
	constexpr int TOTAL_SPRITES = 3;

	constexpr int TILE_WIDTH = 50;
	constexpr int TILE_HEIGHT = 100;

	static int startingType = 0;
}

class LevelEditor
{
public:

	LevelEditor(int x = 0, int = 0, int tiletype = 0);
	~LevelEditor();

	static bool Load(LevelEditor* tiles[]);

	//Replace tiles
	static void PutTile(LevelEditor* tiles[], const SDL_Event& e);

	//The actual render function to call
	void Render();

	static void Save(LevelEditor* tiles[]);

	static void Clean(LevelEditor* tiles[]);

	SDL_Rect GetTileRect();

private:
	SDL_Texture* LoadTex();

	//Func to place tiles; Declared as friend since cannot be used in the static func Load()
	friend bool PlaceTiles(LevelEditor* tiles[]);

	//Setter function
	void RenderMap(int x, int y, SDL_Rect clip);

	SDL_Texture* tile_tex;

	SDL_Rect tile_rectClips[TileProperties::TOTAL_SPRITES];

	SDL_Rect tile_rect;

	int type;

};
