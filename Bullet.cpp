#include "Bullet.h"
#include <iostream>


Bullets::Bullets() : text(font),bulletSpeed(5.0f) {
}

void Bullets::Initialize() {
	font.openFromFile("C:\\Windows\\Fonts\\arial.ttf");
	text.setFont(font); 
	text.setString("Out Of Bullets");
	text.setCharacterSize(30);
	text.setFillColor(sf::Color::White);
}

void Bullets::HandleEvent(const std::optional<sf::Event>& event, Skeleton& skeleton,sf::RenderWindow& window,sf::Sprite& ownerSprite,sf::Clock& clock){
	if (const auto* mousePressed = event->getIf<sf::Event::MouseButtonPressed>()) {
		if (mousePressed->button == sf::Mouse::Button::Left){
			if(bulletsShotted<maxCapacity){
				sBullet b;
				sf::Vector2i mousePosI = sf::Mouse::getPosition(window);
				sf::Vector2f mousePos = sf::Vector2f(mousePosI);
				sf::Vector2f bulletDirection = mousePos - ownerSprite.getPosition();
				std::cout << "Bullet direction x=" << bulletDirection.x << ", y=" << bulletDirection.y << std::endl;
				b.shape.setPosition(ownerSprite.getPosition());
				b.direction = bulletDirection.normalized();
				bullets.push_back(b);
				bulletsShotted++;
				std::cout << "bullets created" << std::endl;
			}
			else {
				isOutOfAmmo = true;
				clock.restart();
			}
		}
	}
}

void Bullets::Update(Skeleton& skeleton,sf::RenderWindow& window) {
	for (size_t i = 0;i < bullets.size(); i++) {
		bullets[i].shape.setPosition(bullets[i].shape.getPosition() + bullets[i].direction * bulletSpeed);
		if (bullets[i].shape.getGlobalBounds().findIntersection(skeleton.sprite.getGlobalBounds())) {
			bullets.erase(bullets.begin() + i);
			i--;
			std::cout << "Enemy Hit" << std::endl;
			continue;
		}
		sf::Vector2u winSize = window.getSize();
		sf::Vector2f pos = bullets[i].shape.getPosition();

		if (pos.x < 0 || pos.x > winSize.x || pos.y < 0 || pos.y > winSize.y) {
			bullets.erase(bullets.begin() + i);
			std::cout << "Out of rendered window" << std::endl;
			i--;
		}
	}
}

void Bullets::Draw(sf::RenderWindow& window,sf::Clock& clock) {
	for (size_t i = 0;i < bullets.size(); i++) {
		window.draw(bullets[i].shape);
	}
	std::cout << "isOutOfAmmo: " << isOutOfAmmo << std::endl;
	std::cout << "clock time: " << clock.getElapsedTime().asSeconds() << std::endl;
	std::cout << "text pos: " << text.getPosition().x << ", " << text.getPosition().y << std::endl;
	std::cout << "text string: " << text.getString().toAnsiString() << std::endl;
	if (isOutOfAmmo) {
		sf::FloatRect bounds = text.getLocalBounds();
		text.setOrigin(bounds.size / 2.f);
		text.setPosition(sf::Vector2f(window.getSize()) / 2.f);
		if (clock.getElapsedTime().asSeconds() <= 2) {
			window.draw(text);
			std::cout << "Text is being drawn" << std::endl;
		}
	}

}