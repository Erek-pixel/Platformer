#include "Game.hpp"
#include <fstream>
#include <iostream>
Game::Game()
	: window(sf::VideoMode({ 1408 ,704 }), "Platformer", sf::Style::Close | sf::Style::Titlebar), world(textureManager)
{
}


void Game::update()
{
	state.dt = state.clock.restart().asSeconds();
}

void Game::handleGravity()
{
	if (!world.player.collision.Grounded)
		SYS::Gravity::update(world.player.transform, state.dt);
}

void Game::handleMovement()
{
	SYS::Movement::updateDash(world.player.input, world.player.dashTimer, world.player.dashCoolDown, state.dt);
	SYS::Movement::decideVelocity(world.player.transform, world.player.input);
	SYS::Movement::moveHorizontaly(world.player.transform, world.player.collision, state.dt);
	SYS::Collision::processHorizontalCollision(world);
	SYS::Movement::moveVerticaly(world.player.transform, world.player.collision, state.dt);
	SYS::Collision::processVerticalCollision(world);
	SYS::Movement::ApplyMovement(world.player);
	SYS::Movement::decideMovementState(world.player);
}

void Game::handleAnimation()
{
	SYS::Animation::update(world.player.sprite, world.player.movmentState, state.dt);
}

void Game::Render()
{
	window.clear();
	SYS::Render::draw(world, window);
	window.display();
}

void Game::run()
{
	while (window.isOpen())
	{
		update();
		SYS::Events::handle(window);
		SYS::Input::update(world.player.input);
		handleGravity();
		handleMovement();
		handleAnimation();
		SYS::Camera::update(world.player, window, 
			sf::Vector2f( world.WorldMap[world.CurrentMap].Width, world.WorldMap[world.CurrentMap].Height ));
		Render();
	}
}
