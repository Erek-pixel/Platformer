#include "System.hpp"

void SYS::Events::handle(sf::RenderWindow& window)
{
	while (std::optional event = window.pollEvent())
	{
		if (event->is<sf::Event::Closed>())
			window.close();
		else if (auto* key = event->getIf<sf::Event::KeyReleased>())
		{
			if (key->scancode == sf::Keyboard::Scancode::Escape)
				window.close();
		}
	}
}