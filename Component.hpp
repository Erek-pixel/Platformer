#include <SFML/Graphics.hpp>
#include <vector>
#pragma once

namespace COMP
{
	struct Transform
	{
		sf::Vector2f velocity = { 0.f, 0.f };
		sf::Vector2f position = { 0.f ,0.f };
		sf::Vector2f size = { 0.f, 0.f };
		sf::Vector2f scale = { 0.f, 0.f };
		float rotation = { 0.f };
		int DirectionFactor = { 1 };
	};

	struct Collision
	{
		sf::FloatRect bounds;
		bool Grounded = { false };
	};

	struct Sprite
	{
		Sprite(const sf::Texture& texture) : sprite(texture) {};
		sf::Sprite sprite;
	};

	struct Health
	{
		int hp = { 0 };
		int maxHP = { 0 };
	};

	struct Input
	{
		bool canDash = { true };
		bool Left = { false };
		bool Right = { false };
		bool Jump = { false };
		bool Dash = { false };
	};

	struct Frame
	{
		float duration = 0.f;
		sf::IntRect frameRect = {};
	};

	template<typename T>
	struct Generation
	{
		int mapID = { 0 };
		int Width = { 0 };
		int Height = { 0 };
		std::vector<T> tileMap;
	};
}