#include "System.hpp"
void SYS::Input::reset(COMP::Input& input) noexcept
{
	input.Dash = { false };
	input.Left = { false };
	input.Right = { false };
	input.Jump = { false };
}



void SYS::Input::update(COMP::Input& input) noexcept
{
	reset(input);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::LShift) && input.canDash)
	{
		input.Dash = { true };
		return;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Space))
		input.Jump = { true };
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Left))
		input.Left = { true };
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Right))
		input.Right = { true };
}