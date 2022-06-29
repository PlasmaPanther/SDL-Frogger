#include "LevelEditor.h"
#include "Graphics.h"
#include <fstream>
#include <iostream>

LevelEditor::LevelEditor(int x, int y, int tiletype)
{

	tile_rect.x = x;
	tile_rect.y = y;
	tile_rect.w = TileProperties::TILE_WIDTH;
	tile_rect.h = TileProperties::TILE_HEIGHT;
	
	type = tiletype;

	this->LoadTex();
	
	//Black
	tile_rectClips[0] = { 0, 0, 0, 0 }; //x, y, w, h
	
	//Red
	tile_rectClips[1] = { 0, 0, TileProperties::TILE_WIDTH, TileProperties::TILE_HEIGHT };
	
	//Yellow
	tile_rectClips[2] = { 50, 0, TileProperties::TILE_WIDTH, TileProperties::TILE_HEIGHT };
	
}

LevelEditor::~LevelEditor() {

	SDL_DestroyTexture(tile_tex);
	tile_tex = nullptr;
}

SDL_Texture* LevelEditor::LoadTex() {

	tile_tex = IMG_LoadTexture(Graphics::GetRenderer(), "tiles.jpg");
	if (tile_tex == nullptr) {
		std::cout << "Tileset not loaded " << IMG_GetError() << std::endl;
	}

	return tile_tex;
}

bool LevelEditor::Load(LevelEditor* tiles[]) {
	if (!PlaceTiles(tiles)) {
		std::cout << "Could not place tiles" << std::endl;
		return false;
	}

	return true;
}

bool PlaceTiles(LevelEditor* tiles[]){
	int x = 0, y = 0;
	const int LEVEL_WIDTH = 800;

	std::ifstream lvl("1.level");

	if (lvl.fail()) {
		std::cout << "Level did not load" << std::endl;
		return false;
	}
	else {

		for (int i = 0; i < TileProperties::TOTAL_TILES; ++i) {
			int tile_type = -1;
			lvl >> tile_type;

			if (lvl.eof()) {
				std::cout << "Error reading file" << std::endl;
				return false;
				break;
			}

			if (tile_type >= 0 && TileProperties::TOTAL_SPRITES <= TileProperties::TOTAL_SPRITES) {
				tiles[i] = new LevelEditor(x, y, tile_type);
			}
			else {
				std::cout << "Error: unknown sprite" << std::endl;
				return false;
				break;
			}

			x += TileProperties::TILE_WIDTH;
			if (x >= LEVEL_WIDTH) {
				x = 0;
				y += TileProperties::TILE_HEIGHT;
			}
		}
	}

	lvl.close();
	return true;
}

void LevelEditor::PutTile(LevelEditor* tiles[], const SDL_Event& e) {
	int mouse_x, mouse_y;

	if (e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN) {
		mouse_x = e.motion.x;
		mouse_y = e.motion.y;

		if (e.button.button == SDL_BUTTON_RIGHT) {
			TileProperties::startingType++;
			if (TileProperties::startingType > 2) {
				TileProperties::startingType = 0;
			}
		}
		else if (e.button.button == SDL_BUTTON_MIDDLE) {
			TileProperties::startingType--;
			if (TileProperties::startingType < 0) {
				TileProperties::startingType = 2;
			}
		}

		if (e.button.button == SDL_BUTTON_LEFT) {
			mouse_x = e.button.x;
			mouse_y = e.button.y;

			for (int i = 0; i < TileProperties::TOTAL_TILES; ++i) {
				SDL_Rect tile = tiles[i]->tile_rect;

				if (mouse_x > tile.x && mouse_x < tile.x + tile.w && mouse_y > tile.y && mouse_y < tile.y + tile.h) {
					delete tiles[i];

					tiles[i] = new LevelEditor(tile.x, tile.y, TileProperties::startingType);
				}
			}
		}
	}
}

void LevelEditor::RenderMap(int x, int y, SDL_Rect clip) {
	SDL_Rect tmp = { x, y, TileProperties::TILE_WIDTH, TileProperties::TILE_HEIGHT };
	
	SDL_RenderCopy(Graphics::GetRenderer(), tile_tex, &clip, &tmp); //Renderer, texture, src rect(tile_rectClips), dst rect(tmp);
}

void LevelEditor::Render()
{
	this->RenderMap(tile_rect.x, tile_rect.y, tile_rectClips[type]);
}

void LevelEditor::Save(LevelEditor* tiles[]) {
	std::ofstream lvl("1.level");

	for (int i = 0; i < TileProperties::TOTAL_TILES; ++i) {
		lvl << tiles[i]->type << " ";
	}
	
	std::cout << "File saved" << std::endl;
	lvl.close();
}

void LevelEditor::Clean(LevelEditor* tiles[]) {
	for (int i = 0; i < TileProperties::TOTAL_TILES; ++i) {
		delete tiles[i];
		tiles[i] = nullptr;
	}
}

SDL_Rect LevelEditor::GetTileRect() {
	return tile_rect;
}
