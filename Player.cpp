#include "Player.hpp"
#include <string>
#include <vector>

Player::Player(const sf::Texture& spriteSheet) :
	sprite(spriteSheet)
{
	transform.position = { 400.f, 1436.f };
	collision.bounds = sf::FloatRect(transform.position, HITBOX_SIZE);
	sprite.transform.scale = { SPRITE_SIZE.x / 14.f, SPRITE_SIZE.y / 15.f };

	dashTimer.time = { 0.2f };
	dashTimer.max_time = { 0.2f };
	dashCoolDown.max_time = { 0.3f };
	dashCoolDown.time = { 0.3f };
	wallJumpTimer.max_time = { 0.2f };
	wallJumpTimer.time = { 0.2f };
	std::vector<std::string> names = { "Idle Right" , "Idle Left", "Walking Right", "Walking Left", "Jumping Right", "Jumping Left", "Dashing Right", "Dashing Left"};
	std::vector<float> duration =
	{
		0.3f, 0.2f, 0.3f, 0.2f,
		0.3f, 0.2f, 0.3f, 0.2f,
		0.2f, 0.3f, 0.2f, 0.3f,
		0.2f, 0.3f, 0.2f, 0.3f,
		0.05f, 0.05f, 0.05f, 0.05f,
		0.05f, 0.05f, 0.05f, 0.05f,
		0.05f, 0.05f, 0.05f, 0.05f,
		0.05f, 0.05f, 0.05f, 0.05f
	};
	for (int i = 0; i < names.size(); i++)
	{
		for (int j = 0; j < 4; j++)
		{
			sprite.addFrame(names[i], COMP::Frame(duration[(i * 4) + j], sf::IntRect(sf::Vector2i(j * 14, i * 15), sf::Vector2i(14, 15)) ));
		}
	}

	sprite.addFrame("Falling Right", { 0.f,sf::IntRect({ 0 , 8 * 15 }, { 14, 15 }) });
	sprite.addFrame("Falling Left", { 0.f,sf::IntRect({ 0 , 9 * 15 }, { 14, 15 }) });
	sprite.AnimatedSpriteSheet.setOrigin(ORIGIN);
	sprite.AnimatedSpriteSheet.setScale(sprite.transform.scale);
}