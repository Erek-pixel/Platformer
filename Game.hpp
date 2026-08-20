#include <SFML/Graphics.hpp>
#include "GameResources.hpp"
#include "GameWorld.hpp"
#include "System.hpp"
#include "Manager.hpp"

#pragma once
class Game
{
public:
	Game();
	void run();
private:
	//  Game State
	enum class State
	{
		Play,
		Transition,
	} gameState = State::Play;

	//  Game's Logic Flow
	void update();
	void handleGravity();
	void handleMovement();
	void handleAnimation();
	void Render();

	//  Game's Components
	sf::RenderWindow window;
	TextureManager textureManager;
	AudioManager audioManager;
	GameWorld world;
	GameState state;
	Random random;
};