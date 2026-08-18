#include "Player.hpp"
#include "Tile.hpp"
#include "Manager.hpp"
#include <vector>
#pragma once
class GameWorld
{
public:
	GameWorld(TextureManager&);
	void _World_Gen(TextureManager& textureManager);

	int CurrentMap = { 0 };
	Player player;
	std::vector<std::vector<Tile::Type>> TileType;
	std::vector<COMP::Generation<Tile>> WorldMap;
};