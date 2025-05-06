#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

#include "Game.hpp"
#include "AssetManager.hpp"
#include "SFMLMath.hpp"

namespace Touch
{
	bool Game::Update()
	{
        const int windowWidth = 800;
        const int windowHeight = 600;

        Touch::AssetManager assets;

        sf::Clock deltaClock;

        assets.LoadTexture("assets/whitedude.png", "white");

        sf::RenderWindow window(sf::VideoMode({ windowWidth, windowHeight }), "Blanco-Strike",
            sf::Style::Titlebar |
            sf::Style::Close);

        window.setFramerateLimit(60);

        sf::Texture playerTex = assets.GetTexture("white");

        sf::Sprite player(playerTex);
        player.setPosition({ 0, 0 });

        sf::Music striker("assets/Striker.mp3");

        striker.play();
        striker.setLooping(true);

        // idk game settings
        const int playerSpeed = 255;


        while (window.isOpen())
        {
            sf::Time deltaTime = deltaClock.restart();

            while (const std::optional event = window.pollEvent())
            {
                if (event->is<sf::Event::Closed>())
                {
                    window.close();
                    return false;
                }
            }


            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
            {
                player.move({ -playerSpeed * deltaTime.asSeconds(), 0.f });

                if (player.getPosition().x <= 0)
                {
                    player.setPosition({ 0.f, player.getPosition().y });
                }
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
            {
                player.move({ playerSpeed * deltaTime.asSeconds(), 0.f });

                if (player.getPosition().x >= windowWidth - player.getGlobalBounds().size.x)
                {
                    player.setPosition({ windowWidth - player.getGlobalBounds().size.x, player.getPosition().y });
                }
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
            {
                player.move({ 0.f, -playerSpeed * deltaTime.asSeconds() });

                if (player.getPosition().y <= 0)
                {
                    player.setPosition({ player.getPosition().x, 0 });
                }
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
            {
                player.move({ 0.f, playerSpeed * deltaTime.asSeconds() });

                if (player.getPosition().y >= windowHeight - player.getGlobalBounds().size.x)
                {
                    player.setPosition({ player.getPosition().x, windowHeight - player.getGlobalBounds().size.x });
                }
            }

            sf::Vector2f mousePos = (sf::Vector2f)sf::Mouse::getPosition(window);
            sf::Vector2f playerToMouse = mousePos - player.getPosition();

            sf::Angle playerAngle(sf::degrees(sf::getRotationAngle(playerToMouse)));

            player.setRotation(playerAngle);

            // drawing functions...

            window.clear(sf::Color::Cyan); // clear to prepare to draw

            // actually draw stuff

            window.draw(player);

            // end of drawing
            window.display();
        }

        return true;
	}
}