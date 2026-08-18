#include <SFML/Graphics.hpp>
#include "Component.hpp"
#pragma once

#ifndef TILE_H
#define TILE_H
#endif
;
class Tile
{
public:
	// Tile Types
	enum class Type
	{
		Grass,
		Dirt,
		Air
	};

	// COMPONENTS

	COMP::Sprite sprite;
	COMP::Collision collision;
	Type type = Type::Grass;

	// CONSTRUCTOR TO LINK THE TEXTURE TO THE SPRITE
	Tile(const sf::Texture& texture, sf::Vector2f position);
private:
	float SIZE = 64.f;
};