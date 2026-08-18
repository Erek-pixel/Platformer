#include "System.hpp"
#include <iostream>

static constexpr sf::Vector2f viewSize = { 1408, 704 };
static sf::View view(sf::FloatRect({ 0.f, 0.f }, viewSize));

void SYS::Camera::update(const Player& player, sf::RenderWindow& window, sf::Vector2f MapSize)
{
	//  Scale The Size To The World Real Size
	MapSize *= 64.f;

	sf::Vector2f center = player.collision.bounds.getCenter();
	view.setCenter(center);

#pragma region Horizontal Correction
	if (center.x - (viewSize.x / 2.f) < 0.f)
		view.setCenter({ (viewSize.x / 2.f), view.getCenter().y });
	else if (center.x + (viewSize.x / 2.f) > MapSize.x)
		view.setCenter({ MapSize.x - (viewSize.x / 2.f), view.getCenter().y });
#pragma endregion

#pragma region Vertical Correction
	if (center.y - (viewSize.y / 2.f) < 0.f)
		view.setCenter({ view.getCenter().x, (viewSize.y / 2.f) });
	else if (center.y + (viewSize.y / 2.f) > MapSize.y)
	{
		view.setCenter({ view.getCenter().x, MapSize.y - (viewSize.y / 2.f) });
	}
#pragma endregion

	window.setView(view);

}