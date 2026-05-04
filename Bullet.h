#pragma once
#include <SFML/Graphics.hpp>
#include "Skeleton.h"

struct sBullet {
	sf::RectangleShape shape{ sf::Vector2f(25, 12) };
	sf::Vector2f direction;
};

class Bullets {
private:
	std::vector <sBullet> bullets;
	int maxCapacity = 30;
	int bulletsShotted = 0;
	float bulletSpeed;

	bool isOutOfAmmo = false;
	sf::Font font;
	sf::Text text;


public:
	Bullets();
	~Bullets() = default;

	void Initialize();
	void Update(Skeleton& skeleton,sf::RenderWindow& window);
	void HandleEvent(const std::optional<sf::Event>& event, Skeleton& skeleton, sf::RenderWindow& window,sf::Sprite& ownerSprite,sf::Clock& clock);
	void Draw(sf::RenderWindow& window, sf::Clock& clock);
};