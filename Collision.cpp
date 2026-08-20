#include "System.hpp"
#include <iostream>


static constexpr float epsilon = 0.01f;

[[nodiscard]] bool SYS::Collision::areIntersect(const COMP::Collision& shape_1, const COMP::Collision& shape_2) noexcept
{
	if (shape_1.bounds.position.x >= shape_2.bounds.position.x + shape_2.bounds.size.x) return false;
	if (shape_1.bounds.position.x + shape_1.bounds.size.x <= shape_2.bounds.position.x) return false;
	if (shape_1.bounds.position.y >= shape_2.bounds.position.y + shape_2.bounds.size.y) return false;
	if (shape_1.bounds.position.y + shape_1.bounds.size.y <= shape_2.bounds.position.y) return false;
	return true;
}

void SYS::Collision::setTilePosition(int Width, int i)
{
	tile.bounds.position = sf::Vector2f(64.f * (i % Width), 64.f * (i / Width));
}

void SYS::Collision::processHorizontalCollision(GameWorld& world)
{
	sf::Vector2f playerPosition = world.player.collision.bounds.position;
	sf::Vector2f playerSize = world.player.collision.bounds.size;
	// Get The Tile That Contains The Top-Left point
	int topLeft = world.WorldMap[world.CurrentMap].Width * (int)(playerPosition.y / 64.f) + (int)(playerPosition.x / 64.f);

	// Get The Tile That Contains The Bottom-Left point
	int bottomLeft = world.WorldMap[world.CurrentMap].Width * (int)((playerPosition.y + playerSize.y) / 64.f) + (int)(playerPosition.x / 64.f);
	// Get The Tile That Contains The Top-Right point
	int topRight = world.WorldMap[world.CurrentMap].Width * (int)(playerPosition.y / 64.f) + (int)((playerPosition.x + playerSize.x) / 64.f);

	// Get The Tile That Contains The Bottom-Right point
	int bottomRight = world.WorldMap[world.CurrentMap].Width * (int)((playerPosition.y + playerSize.y) / 64.f) + (int)((playerPosition.x + playerSize.x) / 64.f);

	switch (world.player.movmentState)
	{
	case Player::State::FallingLeft:
	case Player::State::JumpingLeft:
	case Player::State::WalkingLeft:
	case Player::State::DashingLeft:
		
		// Check From Top-Left To Bottom-Left Verticaly For Intersection And Corrects The Horizontal Position
		for (int i = topLeft; i <= bottomLeft; i += world.WorldMap[world.CurrentMap].Width)
		{
			if (world.TileTypeMap[world.CurrentMap][i] == Tile::Type::Air
				|| world.TileTypeMap[world.CurrentMap][i] == Tile::Type::Platform) continue;
			
			setTilePosition(world.WorldMap[world.CurrentMap].Width, i);
			
			if (areIntersect(world.player.collision, tile))
			{
				world.player.transform.position.x = tile.bounds.position.x + tile.bounds.size.x;
				break;
			}
		}
 		break;
	case Player::State::FallingRight:
	case Player::State::JumpingRight:
	case Player::State::WalkingRight:
	case Player::State::DashingRight:

		// Check From Top-Right To Bottom-Right Verticaly For Intersection And Corrects The Horizontal Position
		for (int i = topRight; i <= bottomRight; i += world.WorldMap[world.CurrentMap].Width)
		{
			if (world.TileTypeMap[world.CurrentMap][i] == Tile::Type::Air
				|| world.TileTypeMap[world.CurrentMap][i] == Tile::Type::Platform) continue;

			setTilePosition(world.WorldMap[world.CurrentMap].Width, i);

			if (areIntersect(world.player.collision, tile))
			{
				world.player.transform.position.x = tile.bounds.position.x - playerSize.x;
				break;
			}

		}
		break;
	}
}

void SYS::Collision::processVerticalCollision(GameWorld& world)
{
	sf::Vector2f playerPosition = world.player.collision.bounds.position;
	sf::Vector2f playerSize = world.player.collision.bounds.size;
	// Get The Tile That Contains The Top-Left point
	int topLeft = world.WorldMap[world.CurrentMap].Width * (int)(playerPosition.y / 64.f) + (int)(playerPosition.x / 64.f);

	// Get The Tile That Contains The Bottom-Left point
	int bottomLeft = world.WorldMap[world.CurrentMap].Width * (int)((playerPosition.y + playerSize.y) / 64.f) + (int)(playerPosition.x / 64.f);
	// Get The Tile That Contains The Top-Right point
	int topRight = world.WorldMap[world.CurrentMap].Width * (int)(playerPosition.y / 64.f) + (int)((playerPosition.x + playerSize.x) / 64.f);

	// Get The Tile That Contains The Bottom-Right point
	int bottomRight = world.WorldMap[world.CurrentMap].Width * (int)((playerPosition.y + playerSize.y) / 64.f) + (int)((playerPosition.x + playerSize.x - epsilon) / 64.f);

	switch (world.player.movmentState)
	{
	case Player::State::JumpingRight:
	case Player::State::JumpingLeft:

		world.player.collision.Grounded = { false };

		// Check From Top-Left To Top-Right Horizontaly For Intersection And Corrects The Vertical Position
		for (int i = topLeft; i <= topRight; i++)
		{
			if (world.TileTypeMap[world.CurrentMap][i] == Tile::Type::Air
				|| world.TileTypeMap[world.CurrentMap][i] == Tile::Type::Platform) continue;
			
			setTilePosition(world.WorldMap[world.CurrentMap].Width, i);

			if (areIntersect(world.player.collision, tile))
			{
				world.player.transform.position.y = tile.bounds.position.y + tile.bounds.size.y;
				world.player.transform.velocity.y = 0.f;
				break;
			}
		}
		break;
	case Player::State::FallingRight:
	case Player::State::FallingLeft:

		// Check From bottom-Left To Bottom-Right Verticaly For Intersection And Corrects The Vertical Position
		world.player.collision.Grounded = { false };
		for (int i = bottomLeft; i <= bottomRight; i++)
		{
			if (world.TileTypeMap[world.CurrentMap][i] == Tile::Type::Air) continue;
			
			setTilePosition(world.WorldMap[world.CurrentMap].Width, i);

			if (areIntersect(world.player.collision, tile))
			{
				world.player.collision.Grounded = { true };
				world.player.transform.position.y = tile.bounds.position.y - playerSize.y;
				world.player.transform.velocity.y = 0.f;
				break;
			}
		}
		break;
	default:
		// Check If There Is A Solid Block Under The Player To Stand On 

		for (int i = bottomLeft; i <= bottomRight; i++)
		{
			if (world.TileTypeMap[world.CurrentMap][i] == Tile::Type::Air) continue;
			world.player.collision.Grounded = { true };
			world.player.input.canDash = { true };
			return;
		}
		world.player.collision.Grounded = { false };
		break;
	}

}