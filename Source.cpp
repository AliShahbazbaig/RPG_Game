#include <SFML/Graphics.hpp>
#include <iostream>



int main()
{
	sf::ContextSettings settings;
	settings.antiAliasingLevel = 8;

	sf::RenderWindow window(sf::VideoMode({ 1920,1080 }), "RPG Game", sf::Style::Default, sf::State::Windowed, settings);
	window.setFramerateLimit(60);
	try
	{
		struct Bullets
		{
			sf::RectangleShape shape{sf::Vector2f(25, 12)};
			sf::Vector2f direction;
		};
		sf::Texture enemyTexture;
		sf::Texture playerTexture;
		std::vector<Bullets> Bullet;
		/*sf::RectangleShape Bullet(sf::Vector2f(25, 12));*/
		float bulletSpeed = 8.f;

		//----------------------------------------- Player -----------------------------------------------------------
		if (!playerTexture.loadFromFile("assets/Player/Texture/Spritesheet.png")) {
			throw std::runtime_error("Player Spritesheet Faild to Load");

		}
		std::cout << "Player Spritsheet Loaded successfully!" << std::endl;
		sf::Sprite playerSprite(playerTexture);

		//X,Y,Width,Height
		int xIndex = 0;
		int yIndex = 3;
		playerSprite.setTextureRect(sf::IntRect(sf::Vector2i(xIndex * 64, yIndex * 64), sf::Vector2i(64, 64)));
		playerSprite.scale(sf::Vector2f(2, 2));
		playerSprite.setPosition(sf::Vector2f(1650, 600));
		/*Bullet.setPosition(playerSprite.getPosition());*/

		//----------------------------------------- Player -----------------------------------------------------------



		//----------------------------------------- Enemy ------------------------------------------------------------

		if (!enemyTexture.loadFromFile("assets/Skeleton/Texture/Spritesheet.png"))
			throw std::runtime_error("Enemy Spritesheet Faild to Load!");

		std::cout << "Enemy Spritsheet Loaded successfully!" << std::endl;
		sf::Sprite enemySprite(enemyTexture);
		//X,Y,Width,Height
		int xIndex_ = 0;
		int yIndex_ = 2;
		enemySprite.setTextureRect(sf::IntRect(sf::Vector2i(xIndex_ * 64, yIndex_ * 64), sf::Vector2i(64, 64)));
		enemySprite.setPosition(sf::Vector2f(400, 100));
		enemySprite.scale(sf::Vector2f(2, 2));
		/*enemySprite.setOrigin()*/


		//----------------------------------------- Enemy ------------------------------------------------------------
		bool isMoving = false;

		//-------------------------------------- Bullet Direction ----------------------------------------------------
		//sf::Vector2f bulletDirection = enemySprite.getPosition() - Bullet.getPosition();
		//bulletDirection=bulletDirection.normalized();

		//-------------------------------------- Bullet Direction ----------------------------------------------------


		while (window.isOpen()) {
			while (const std::optional event = window.pollEvent()) {
				if (event->is<sf::Event::Closed>()) {
					window.close();
				}

				if (const auto* mousePressed=event->getIf<sf::Event::MouseButtonPressed>()) {
					if (mousePressed->button == sf::Mouse::Button::Left) {
						Bullets bullet;
						bullet.shape.setPosition(playerSprite.getPosition());
						sf::Vector2f bulletDirection = enemySprite.getPosition() - bullet.shape.getPosition();
						bulletDirection = bulletDirection.normalized();
						bullet.direction = bulletDirection;
						Bullet.push_back(bullet);
						std::cout << "Bullet created" << std::endl;
					}
				}
			}

			//Bullet.setPosition(Bullet.getPosition() + bulletDirection * bulletSpeed);

			//depends on famerate 
			sf::Vector2f position = playerSprite.getPosition();

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
			{
				if(position.x+64<1920){
					playerSprite.setPosition(position + sf::Vector2f(1, 0));
					yIndex = 3;
					isMoving = true;
				}
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
			{
				if (position.x >0) {
					playerSprite.setPosition(position - sf::Vector2f(1, 0));
					yIndex = 1;
					isMoving = true;
				}
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
			{
				if (position.y>0) {
					playerSprite.setPosition(position - sf::Vector2f(0, 1));
					yIndex = 0;
					isMoving = true;
				}
			}


			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
			{
				if (position.y + 64 < 1080) {
					playerSprite.setPosition(position + sf::Vector2f(0, 1));
					yIndex = 2;
					isMoving = true;
				}
			}

			if(isMoving){
				xIndex++;
				if (xIndex > 8)
					xIndex = 0;

				playerSprite.setTextureRect(sf::IntRect(sf::Vector2i(xIndex * 64, yIndex * 64), sf::Vector2i(64, 64)));
				isMoving = false;
			}


			for (size_t i = 0;i < Bullet.size(); i++) {
				
				Bullet[i].shape.setPosition(Bullet[i].shape.getPosition() + Bullet[i].direction * bulletSpeed);
				if (Bullet[i].shape.getGlobalBounds().findIntersection(enemySprite.getGlobalBounds())) {

					std::cout<<"x = " <<Bullet[i].shape.getPosition().x << ", y = " << Bullet[i].shape.getPosition().y << std::endl;
					Bullet.erase(Bullet.begin() + i);
				}
			}
			window.clear();
			window.draw(enemySprite);     
			window.draw(playerSprite);
			for (size_t i = 0;i < Bullet.size(); i++) {
				window.draw(Bullet[i].shape);
			}
			window.display();
			
		}
	}
	catch (const std::exception& e) {
		std::cerr << "Error" << e.what() << std::endl;
	}

}