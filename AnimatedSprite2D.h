#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <vector>
#include "Component.hpp"
#include "Timer.hpp"
#pragma once


class AnimatedSprite2D
{
public:
	AnimatedSprite2D(const sf::Texture& SpritesSheet)
		: AnimatedSpriteSheet(SpritesSheet)
	{ }
	COMP::Transform transform;
	sf::Sprite AnimatedSpriteSheet;
	Timer frameTimer;
	std::unordered_map<std::string, std::vector<COMP::Frame>> Frames;

	void addFrame(const std::string&, const COMP::Frame&);

private:
	int CurrentSprite = 0;
};