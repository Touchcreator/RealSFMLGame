#include <map>
#include <iostream>
#include <optional>

#include <SFML/Graphics.hpp>
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

        long bulletCount = 0;

        Touch::AssetManager assets;

        sf::Clock deltaClock;

        assets.LoadTexture("assets/whitedude.png", "white");
        assets.LoadTexture("assets/bullet.png", "bullet");

        sf::RenderWindow window(sf::VideoMode({ windowWidth, windowHeight }), "Blanco-Strike",
            sf::Style::Titlebar |
            sf::Style::Close);

        window.setFramerateLimit(60);

        sf::Texture playerTex = assets.GetTexture("white");
        sf::Texture bulletTex = assets.GetTexture("bullet");

        std::map<long, sf::Sprite> bullets;

        sf::Sprite player(playerTex);
        

        player.setOrigin({ 16, 16 });
        player.setPosition({ windowWidth / 2, windowHeight / 2 });

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

                if (event->is<sf::Event::MouseButtonReleased>())
                {
                    std::cout << "lets say you just shot a bullet" << std::endl;
                }
            }


            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
            {
                player.move({ -playerSpeed * deltaTime.asSeconds(), 0.f });

                if (player.getPosition().x <= player.getGlobalBounds().size.x / 2)
                {
                    player.setPosition({ player.getGlobalBounds().size.x / 2 , player.getPosition().y });
                }
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
            {
                player.move({ playerSpeed * deltaTime.asSeconds(), 0.f });

                if (player.getPosition().x >= windowWidth - player.getGlobalBounds().size.x / 2)
                {
                    player.setPosition({ windowWidth - player.getGlobalBounds().size.x / 2, player.getPosition().y });
                }
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
            {
                player.move({ 0.f, -playerSpeed * deltaTime.asSeconds() });

                if (player.getPosition().y <= player.getGlobalBounds().size.y / 2)
                {
                    player.setPosition({ player.getPosition().x, player.getGlobalBounds().size.y / 2 });
                }
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
            {
                player.move({ 0.f, playerSpeed * deltaTime.asSeconds() });

                if (player.getPosition().y >= windowHeight - player.getGlobalBounds().size.y / 2)
                {
                    player.setPosition({ player.getPosition().x, windowHeight - player.getGlobalBounds().size.x / 2 });
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

            //std::map<long, sf::Sprite>::iterator it; // stuff for drawing bullets

            /*for (it = bullets.begin(); it != bullets.end(); it++)
            {
                window.draw(it->second);
            } */



            // end of drawing
            window.display();
        }

        return true;
	}
}