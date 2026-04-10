#include "Player.h"
#include <iostream>


void Player::Initialize() {

}

void Player::Load() {
	try {
		if (!texture.loadFromFile("assets/Player/Texture/Spritesheet.png")) {
			throw std::runtime_error("Player Texture not Found");
		}
		sprite.setTexture(texture);
		int xIndex_ = 0;
		int yIndex_ = 2;
		sprite.setTextureRect(sf::IntRect(sf::Vector2i(xIndex_ * 64, yIndex_ * 64), sf::Vector2i(64, 64)));
		sprite.setPosition(sf::Vector2f(400, 100));
		sprite.scale(sf::Vector2f(2, 2));
	}
	catch (const std::exception& e) {
		std::cerr << "Error" << e.what() << std::endl;
	}

}

void Player::Update(Skeleton& skeleton) {
	int xIndex = 0;
	int yIndex = 3;
	bool isMoving = false;

	sf::Vector2f position = sprite.getPosition();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		if (position.x + 64 < 1920) {
			sprite.setPosition(position + sf::Vector2f(1, 0));
			yIndex = 3;
			isMoving = true;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
	{
		if (position.x > 0) {
			sprite.setPosition(position - sf::Vector2f(1, 0));
			yIndex = 1;
			isMoving = true;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
	{
		if (position.y > 0) {
			sprite.setPosition(position - sf::Vector2f(0, 1));
			yIndex = 0;
			isMoving = true;
		}
	}


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
	{
		if (position.y + 64 < 1080) {
			sprite.setPosition(position + sf::Vector2f(0, 1));
			yIndex = 2;
			isMoving = true;
		}
	}

	if (isMoving) {
		xIndex++;
		if (xIndex > 8)
			xIndex = 0;

		sprite.setTextureRect(sf::IntRect(sf::Vector2i(xIndex * 64, yIndex * 64), sf::Vector2i(64, 64)));
		isMoving = false;
	}

	for (size_t i = 0;i < bullets.size(); i++) {

		bullets[i].shape.setPosition(bullets[i].shape.getPosition() + bullets[i].direction * bulletSpeed);
		if (bullets[i].shape.getGlobalBounds().findIntersection(skeleton.sprite.getGlobalBounds())) {

			std::cout << "x = " << bullets[i].shape.getPosition().x << ", y = " << bullets[i].shape.getPosition().y << std::endl;
			bullets.erase(bullets.begin() + i);
		}
	}

}

void Player::HandleEvent(sf::Event& event, Skeleton& skeleton) {
	if (const auto* mousePressed = event.getIf<sf::Event::MouseButtonPressed>()) {
		if (mousePressed->button == sf::Mouse::Button::Left) {
			Bullets bullet;
			bullet.shape.setPosition(sprite.getPosition());
			sf::Vector2f bulletDirection = skeleton.sprite.getPosition() - bullet.shape.getPosition();
			bulletDirection = bulletDirection.normalized();
			bullet.direction = bulletDirection;
			bullets.push_back(bullet);
			std::cout << "bullets created" << std::endl;
		}
	}
}

void Player::Draw(sf::RenderWindow& window) {
	window.draw(sprite);
}