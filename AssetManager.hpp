#pragma once

#include <map>
#include <string>

#include "SFML/Graphics.hpp"

namespace Touch
{
	class AssetManager
	{
	public:
		AssetManager() {};
		~AssetManager() {};

		void LoadTexture(std::string filename, std::string name);
		sf::Texture GetTexture(std::string name);

		void LoadFont(std::string filename, std::string name);
		sf::Font GetFont(std::string name);

	private:
		std::map<std::string, sf::Texture> _textures;
		std::map<std::string, sf::Font> _fonts;
	};
}

