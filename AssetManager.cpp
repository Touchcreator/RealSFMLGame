#include "AssetManager.hpp"

namespace Touch
{
	void AssetManager::LoadTexture(std::string filename, std::string name)
	{
		sf::Texture tex;

		if (tex.loadFromFile(filename))
		{
			this->_textures[name] = tex;
		}
	}
	sf::Texture AssetManager::GetTexture(std::string name)
	{
		return this->_textures[name];
	}

	void AssetManager::LoadFont(std::string filename, std::string name)
	{
		sf::Font font;

		if (font.openFromFile(filename))
		{
			this->_fonts[name] = font;
		}
	}
	sf::Font AssetManager::GetFont(std::string name)
	{
		return this->_fonts[name];
	}
}