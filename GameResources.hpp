#include <SFML/Graphics.hpp>
#include <random>
#pragma once

struct GameState
{
	sf::Clock clock;
	float dt = { 0.f };
};

struct Random
{
	static inline std::mt19937 gen{ std::random_device{}() };
	int getRandom(int min, int max)
	{
		return std::uniform_int_distribution<>(min, max)(gen);
	}
};