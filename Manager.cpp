#include "Manager.hpp"
#include <iostream>
#include <array>

TextureManager::TextureManager()
{
	const unsigned int Length = 3;
	
	std::array<std::string, Length> textureNames =
	{ "playerAnimatedSheet", "solidBlock", "air"};

	for (unsigned int i = 0; i < Length; i++)
	{
		if (!textures[textureNames[i]].loadFromFile("assets/textures/" + textureNames[i] + ".png"))
		{
			std::cerr << "Couldn't Load File [" << textureNames[i] + ".png" << "] !!\n";
		}
	}
}

const sf::Texture& TextureManager::getTexture(const std::string& name)
{
	return textures.at(name);
}

AudioManager::AudioManager()
{
	const unsigned int Length = 2;

	std::array<const char*, Length> bufferPaths =
	{ "assets/audio/Jump.mp3", "assets/audio/Damage.mp3" };

	std::array<const char*, Length> textureNames =
	{ "Jump", "Damage" };

	for (unsigned int i = 0; i < Length; i++)
	{
		if (!buffers[textureNames[i]].loadFromFile(bufferPaths[i]))
		{
			std::cerr << "Couldn't Load File [" << bufferPaths[i] << "] !!\n";
			return;
		}
	}
}

const sf::SoundBuffer& AudioManager::getBuffer(const std::string& name)
{
	return buffers.at(name);
}

FontManager::FontManager()
{
	const unsigned int Length = 1;

	std::array<const char*, Length> texturePaths =
	{ "assets/fonts/arial.ttf" };

	std::array<const char*, Length> textureNames = { "arial" };

	for (unsigned int i = 0; i < Length; i++)
	{
		if (!fonts[textureNames[i]].openFromFile(texturePaths[i]))
		{
			std::cerr << "Couldn't Load File [" << texturePaths[i] << "] !!\n";
			return;
		}
	}
}

const sf::Font& FontManager::getFont(const std::string& name)
{
	return fonts.at(name);
}