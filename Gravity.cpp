#include "System.hpp"

void SYS::Gravity::update(COMP::Transform& transform, float dt) noexcept
{
	if (transform.velocity.y < GRAVITY)
		transform.velocity.y += (GRAVITY * dt);
}