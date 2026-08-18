#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <unordered_map>
#include <string>
#pragma once

class TextureManager
{
public:
	TextureManager();
	const sf::Texture& getTexture(const std::string& name);
private:
	std::unordered_map<std::string, sf::Texture> textures;
};

class AudioManager
{
public:
	AudioManager();
	const sf::SoundBuffer& getBuffer(const std::string& name);
private:
	std::unordered_map<std::string, sf::SoundBuffer> buffers;
};

class FontManager
{
public:
	FontManager();
	const sf::Font& getFont(const std::string& name);
private:
	std::unordered_map<std::string, sf::Font> fonts;
};