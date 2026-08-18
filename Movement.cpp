#include "System.hpp"
#include <iostream>

void SYS::Movement::updateDash(COMP::Input& input, Timer& dashTimer, Timer& dashCoolDown, float dt)
{
	if (dashCoolDown.is_counting)
	{
		input.Dash = { false };
		dashCoolDown.update(dt);
		return;
	}
	else
		dashCoolDown.reset();
	if (dashTimer.is_counting)
	{
		input = {};
		input.Dash = { true };
		dashTimer.update(dt);
		return;
	}
	else if (dashTimer.time_up)
	{
		dashCoolDown.start();
		dashTimer.reset();
		input.canDash = { false };
		return;
	}
	if (input.Dash && input.canDash)
		dashTimer.start();
	else if (!input.canDash)
		input.Dash = { false };
}

void SYS::Movement::decideVelocity(COMP::Transform& transform, COMP::Input input) noexcept
{
	if (input.Dash)
	{
		transform.velocity = { 2.4f * transform.DirectionFactor * MAX_VELOCITY.x, 0.f };
		return;
	}
	else if (input.Left)
	{
		transform.DirectionFactor = -1;
		transform.velocity.x = transform.DirectionFactor * MAX_VELOCITY.x;
	}
	else if (input.Right)
	{
		transform.DirectionFactor = 1;
		transform.velocity.x = transform.DirectionFactor * MAX_VELOCITY.x;
	}
	else
		transform.velocity.x = { 0.f };
	if ((transform.velocity.y == 0.f) && (input.Jump))
		transform.velocity.y = MAX_VELOCITY.y;
	else if ((transform.velocity.y < 0.f) && (!input.Jump))
		transform.velocity.y = 0.f;
}

void SYS::Movement::moveHorizontaly(COMP::Transform& transform, COMP::Collision& collision, float dt) noexcept
{
	transform.position.x += transform.velocity.x * dt;
	collision.bounds.position = transform.position;
}

void SYS::Movement::moveVerticaly(COMP::Transform& transform, COMP::Collision& collision, float dt) noexcept
{
	transform.position.y += transform.velocity.y * dt;
	collision.bounds.position = transform.position;
}

void SYS::Movement::ApplyMovement(Player& player)
{
	player.sprite.AnimatedSpriteSheet.setPosition(player.transform.position + player.SCALED_ORIGIN);
}

void SYS::Movement::decideMovementState(Player& player)
{
	sf::Vector2f& velocity = player.transform.velocity;
	if (velocity.x > 0.f)
	{
		if (player.input.Dash) player.movmentState = Player::State::DashingRight;
		else if (velocity.y > 0.f) player.movmentState = Player::State::FallingRight;
		else if (velocity.y < 0.f) player.movmentState = Player::State::JumpingRight;
		else if (velocity.y == 0.f) player.movmentState = Player::State::WalkingRight;
	}
	else if (velocity.x < 0.f)
	{
		if (player.input.Dash) player.movmentState = Player::State::DashingLeft;
		else if (player.climping) player.movmentState = Player::State::ClimpingLeft;
		else if (velocity.y > 0.f) player.movmentState = Player::State::FallingLeft;
		else if (velocity.y < 0.f) player.movmentState = Player::State::JumpingLeft;
		else if (velocity.y == 0.f) player.movmentState = Player::State::WalkingLeft;
	}

	else if (velocity.x == 0.f)
	{
		if (velocity.y >= 0.f && player.movmentState == Player::State::DashingLeft)
		{
			if (player.collision.Grounded)
				player.movmentState = Player::State::IdleLeft;
			else
				player.movmentState = Player::State::FallingLeft;
		}
		else if (velocity.y >= 0.f && player.movmentState == Player::State::DashingRight)
		{
			if (player.collision.Grounded)
				player.movmentState = Player::State::IdleRight;
			else
				player.movmentState = Player::State::FallingRight;
		}
		else if (velocity.y > 0.f && player.movmentState == Player::State::JumpingLeft) player.movmentState = Player::State::FallingLeft;
		else if ((velocity.y > 0.f) && player.movmentState == Player::State::JumpingRight) player.movmentState = Player::State::FallingRight;
		else if ((velocity.y < 0.f) && (player.movmentState == Player::State::WalkingLeft || player.movmentState == Player::State::IdleLeft)) 
			player.movmentState = Player::State::JumpingLeft;
		else if ((velocity.y < 0.f) && (player.movmentState == Player::State::WalkingRight || player.movmentState == Player::State::IdleRight)) 
			player.movmentState = Player::State::JumpingRight;
		else if ((velocity.y == 0.f) && (player.movmentState == Player::State::WalkingLeft || player.movmentState == Player::State::FallingLeft))
			player.movmentState = Player::State::IdleLeft;
		else if ((velocity.y == 0.f) && (player.movmentState == Player::State::WalkingRight || player.movmentState == Player::State::FallingRight))
			player.movmentState = Player::State::IdleRight;
	}
}