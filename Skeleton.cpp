#include "Skeleton.h"
#include <iostream>

void Skeleton::Initialize() {
	size = sf::Vector2i(64, 64);

	boundingRectangle.setFillColor(sf::Color::Transparent);
	boundingRectangle.setOutlineColor(sf::Color::Red);
	boundingRectangle.setOutlineThickness(1);
}

void Skeleton::Load() {
	try {
		if (!texture.loadFromFile("assets/Skeleton/Texture/Spritesheet.png")) {
			throw std::runtime_error("Skeleton Texture not Found");
		}
		std::cout << "Skeleton Texture Loaded" << std::endl;
		sprite.setTexture(texture);
		sprite.setTextureRect(sf::IntRect(sf::Vector2i(xIndex_ * size.x, yIndex_ * size.y), sf::Vector2i(size.x, size.y)));
		sprite.setPosition(sf::Vector2f(400, 100));
		sprite.scale(sf::Vector2f(2, 2));
		//sprite.setOrigin(sf::Vector2f(size.x / 2.f, size.y / 2.f));
		boundingRectangle.setSize(sf::Vector2f(size.x * sprite.getScale().x, size.y * sprite.getScale().y));

	}
	catch (const std::exception& e) {
		std::cerr << "Error" << e.what() << std::endl;
	}

}

void Skeleton::Update() {
	boundingRectangle.setPosition(sprite.getPosition());
}

void Skeleton::Draw(sf::RenderWindow& window) {
	window.draw(sprite);
	window.draw(boundingRectangle);
}