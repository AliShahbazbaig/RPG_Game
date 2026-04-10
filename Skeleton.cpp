#include "Skeleton.h"
#include <iostream>

void Skeleton::Initialize() {

}

void Skeleton::Load() {
	try {
		if (!texture.loadFromFile("assets/Skeleton/Texture/Spritesheet.png")) {
			throw std::runtime_error("Skeleton Texture not Found");
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
void Skeleton::Draw(sf::RenderWindow& window) {
	window.draw(sprite);
}