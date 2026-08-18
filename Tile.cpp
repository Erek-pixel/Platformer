#include "Tile.hpp"

Tile::Tile(const sf::Texture& texture, sf::Vector2f position) : sprite(texture)
{
	sf::Vector2f textureSize = sf::Vector2f(texture.getSize());
	sf::Vector2f scale = { 64.f / textureSize.x, 64.f / textureSize.y};
	sprite.sprite.setScale(scale);

	sprite.sprite.setPosition(position);
	collision.bounds.position = position;
	collision.bounds.size = { SIZE, SIZE };
}