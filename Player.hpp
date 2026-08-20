#include "Component.hpp"
#include "AnimatedSprite2D.h"
#include "Timer.hpp"
#pragma once

class Player
{
public:
	enum class State
	{
		IdleLeft,
		IdleRight,
		WalkingLeft,
		WalkingRight,
		JumpingLeft,
		JumpingRight,
		FallingLeft,
		FallingRight,
		DashingLeft,
		DashingRight,
		ClimpingLeft,
		ClimpingRight,
		WallJumpLeft,
		WallJumpRight
	};
	Player(const sf::Texture& SpritesSheet);
	AnimatedSprite2D sprite;
	State movmentState = { State::FallingRight };
	bool climping = { false };

	//  Components
	COMP::Collision collision;
	COMP::Health health;
	COMP::Transform transform;
	COMP::Input input;

	//  Movement Timers
	Timer dashTimer;
	Timer dashCoolDown;
	Timer wallJumpTimer;

	static constexpr sf::Vector2f SCALED_ORIGIN = { 20.f, 100.f };
	static constexpr sf::Vector2f HITBOX_SIZE = { 40.f, 100.f };
	static constexpr sf::Vector2f PLATFORM_HITBOX_SIZE = { 40.f, 10.f };
private:
	static constexpr sf::Vector2f SPRITE_SIZE = { 60.f, 120.f };
	static constexpr sf::Vector2f ORIGIN = { 7.f, 15.f };
};