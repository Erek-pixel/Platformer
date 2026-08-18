#include "System.hpp"

void SYS::Render::draw(GameWorld& world, sf::RenderWindow& window)
{
	for (auto& tile : world.WorldMap[world.CurrentMap].tileMap)
	{
		if (tile.type != Tile::Type::Air)
			window.draw(tile.sprite.sprite);
	}
	window.draw(world.player.sprite.AnimatedSpriteSheet);
}