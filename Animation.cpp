#include "System.hpp"

static std::string to_string(const Player::State& movementState)
{
	switch (movementState)
	{
	case Player::State::IdleLeft:
		return "Idle Left";
	case Player::State::IdleRight:
		return "Idle Right";
	case Player::State::WalkingLeft:
		return "Walking Left";
	case Player::State::WalkingRight:
		return "Walking Right";
	case Player::State::JumpingLeft:
		return "Jumping Left";
	case Player::State::JumpingRight:
		return "Jumping Right";
	case Player::State::FallingLeft:
		return "Falling Left";
	case Player::State::FallingRight:
		return "Falling Right";
	case Player::State::DashingLeft:
		return "Dashing Left";
	case Player::State::DashingRight:
		return "Dashing Right";
	default:
		return "Idle Left";
	}
}


static void progressFrames(AnimatedSprite2D& spriteSheet, int* counter, const std::string& name, bool changed)
{
	if (spriteSheet.frameTimer.time_up || changed)
	{
		(*counter)++;
		(*counter) %= spriteSheet.Frames[name].size();
		spriteSheet.AnimatedSpriteSheet.setTextureRect(spriteSheet.Frames[name][*counter].frameRect);
		spriteSheet.frameTimer.max_time = spriteSheet.Frames[name][*counter].duration;
		spriteSheet.frameTimer.restart();
	}
}

void SYS::Animation::update(AnimatedSprite2D& spriteSheet, const Player::State& movementState, float dt)
{	
	bool changed = movementState != previousState;

	if (changed)
		counter = 3;
	previousState = movementState;
	progressFrames(spriteSheet, &counter, std::move(to_string(movementState)), changed);
	spriteSheet.frameTimer.update(dt);
}