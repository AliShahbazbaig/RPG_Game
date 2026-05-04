#include "Player.h"
#include <iostream>


void Player::Initialize() {
	size = sf::Vector2i(64, 64);

	boundingRectangle.setFillColor(sf::Color::Transparent);
	boundingRectangle.setOutlineColor(sf::Color::Blue);
	boundingRectangle.setOutlineThickness(1);
	bullets.Initialize();
}

void Player::Load() {
	try {
		if (!texture.loadFromFile("assets/Player/Texture/Spritesheet.png")) {
			throw std::runtime_error("Player Texture not Found");
		}
		std::cout << "Player Texture Loaded" << std::endl;
		sprite.setTexture(texture);
		sprite.setTextureRect(sf::IntRect(sf::Vector2i(xIndex * size.x, yIndex * size.y), sf::Vector2i(size.x, size.y)));
		sprite.setPosition(sf::Vector2f(1650, 600));
		sprite.scale(sf::Vector2f(2, 2));
		boundingRectangle.setSize(sf::Vector2f(size.x * sprite.getScale().x, size.y * sprite.getScale().y));
	}
	catch (const std::exception& e) {
		std::cerr << "Error" << e.what() << std::endl;
	}

}

void Player::Update(Skeleton& skeleton,sf::RenderWindow& window) {
	bool isMoving = false;

	sf::Vector2f position = sprite.getPosition();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		if (position.x + 64 < 1920) {
			sprite.setPosition(position + sf::Vector2f(1, 0)*playerSpeed);
			yIndex = 3;
			isMoving = true;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
	{
		if (position.x > 0) {
			sprite.setPosition(position - sf::Vector2f(1, 0)*playerSpeed);
			yIndex = 1;
			isMoving = true;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
	{
		if (position.y > 0) {
			sprite.setPosition(position - sf::Vector2f(0, 1)*playerSpeed);
			yIndex = 0;
			isMoving = true;
		}
	}


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
	{
		if (position.y + 64 < 1080) {
			sprite.setPosition(position + sf::Vector2f(0, 1)*playerSpeed);
			yIndex = 2;
			isMoving = true;
		}
	}

	if (isMoving) {
		if (isMoving) {
			frameTimer++;
			if (frameTimer >= frameDelay) {
				frameTimer = 0;
				xIndex++;
				if (xIndex > 8)
					xIndex = 0;
			}
			sprite.setTextureRect(sf::IntRect(sf::Vector2i(xIndex * size.x, yIndex * size.y), sf::Vector2i(size.x, size.y)));
		}
	}

	////direct creation
	//for (size_t i = 0;i < bullets.size(); i++) {
	//	bullets[i].shape.setPosition(bullets[i].shape.getPosition() + bullets[i].direction * bulletSpeed);
	//	if (bullets[i].shape.getGlobalBounds().findIntersection(skeleton.sprite.getGlobalBounds())) {
	//		bullets.erase(bullets.begin() + i);
	//		std::cout << "Enemy Hit" << std::endl;
	//	}
	//}

	

	//class creation
	bullets.Update(skeleton,window);


	std::optional <sf::Rect<float>> enemy = sprite.getGlobalBounds().findIntersection(skeleton.sprite.getGlobalBounds());
	if (enemyHit=false && sprite.getGlobalBounds().findIntersection(skeleton.sprite.getGlobalBounds())) {
		enemyHit = true;
		std::cout << "Collision with enemy" << std::endl;
	}

	boundingRectangle.setPosition(sprite.getPosition());
}

void Player::HandleEvent(const std::optional<sf::Event>& event, Skeleton& skeleton,sf::RenderWindow& window,sf::Clock& clock) {
	//if (const auto* mousePressed = event->getIf<sf::Event::MouseButtonPressed>()) {
	//	if (mousePressed->button == sf::Mouse::Button::Left) {
	//		Bullets bullet;
	//		bullet.shape.setPosition(sprite.getPosition());
	//		/*sf::Vector2f bulletDirection = skeleton.sprite.getPosition() - bullet.shape.getPosition();
	//		bulletDirection = bulletDirection.normalized();*/
	//		sf::Vector2i mousePosI = sf::Mouse::getPosition(window);
	//		sf::Vector2f mousePos = sf::Vector2f(mousePosI);
	//		sf::Vector2f bulletDirection = mousePos - sprite.getPosition();
	//		bullet.direction = bulletDirection.normalized();
	//		bullets.push_back(bullet);
	//		std::cout << "bullets created" << std::endl;
	//	}
	//}
	bullets.HandleEvent(event, skeleton, window,sprite,clock);
}

void Player::Draw(sf::RenderWindow& window,sf::Clock& clock) {
	if (!enemyHit) {
		window.draw(sprite);
		window.draw(boundingRectangle);
		/*for (size_t i = 0;i < bullets.size(); i++) {
			window.draw(bullets[i].shape);
		}*/
		bullets.Draw(window,clock);
	}
}