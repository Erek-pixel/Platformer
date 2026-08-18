#include "AnimatedSprite2D.h"

void AnimatedSprite2D::addFrame(const std::string& animation, const COMP::Frame& frame)
{
	Frames[animation].emplace_back(frame);
}