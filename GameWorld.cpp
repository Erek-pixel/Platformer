#include "GameWorld.hpp"
#include <iostream>
#include <fstream>
#include <string>


inline constexpr size_t Map_Number = { 1 };

static void fillMap(int Height, std::ifstream& file, std::string& map)
{
	for (int i = 0; i <= Height; i++)
	{
		std::string line = {};
		std::getline(file, line);
		map.append(std::move(line));
	}
}

static void fillTileMap(int Width, int area, const std::string& map,std::vector<Tile>& tileMap, std::vector<Tile::Type>& tileTypeMap, TextureManager& textureManager)
{
	for (int i = 0; i < area; i++)
	{
		if (map[i] == '#')
		{
			sf::Vector2f position = sf::Vector2f(64.f * (i % Width), 64.f * (i / Width));
			tileMap.emplace_back(Tile(textureManager.getTexture("solidBlock"), position));
			tileTypeMap.emplace_back(Tile::Type::Solid);
		}
		else if (map[i] == '.')
		{
			sf::Vector2f position = sf::Vector2f(64.f * (i % Width), 64.f * (i / Width));
			tileTypeMap.emplace_back(Tile::Type::Air);
		}
	}
}

GameWorld::GameWorld(TextureManager& textureManager)
	: player(textureManager.getTexture("playerAnimatedSheet"))
{
	_World_Gen(textureManager);
}

void GameWorld::_World_Gen(TextureManager& textureManager)
{
	WorldMap.reserve(Map_Number);
	TileTypeMap.reserve(Map_Number);

	std::ifstream file;
	for (int i = 0; i < Map_Number; i++)
	{
		WorldMap.emplace_back(COMP::Generation<Tile>{});
		TileTypeMap.emplace_back(std::vector<Tile::Type>{});

		file.open("map_" + std::to_string(i) + ".txt");
		if (!file.is_open())
		{
			std::cerr << "Couldn't Open File [map_" << i << ".txt]\n";
			return;
		}
		std::string map = {};

		file >> WorldMap[i].Width;
		file >> WorldMap[i].Height;
		
		size_t area = WorldMap[i].Width * WorldMap[i].Height;
		
		WorldMap[i].tileMap.reserve(area);
		TileTypeMap.reserve(area);
		
		fillMap(WorldMap[i].Height, file, map);
		fillTileMap(WorldMap[i].Width, area, map, WorldMap[i].tileMap, TileTypeMap[i], textureManager);
	}
}