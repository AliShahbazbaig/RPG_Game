#pragma once
#include <SFML/Graphics.hpp>
#include "Skeleton.h" 


struct Bullets
{
	sf::RectangleShape shape{sf::Vector2f(25, 12)};
	sf::Vector2f direction;
};

class Player
{
private:
	sf::Texture texture;

	std::vector<Bullets> bullets;
	float bulletSpeed = 0.5f;

public:
	sf::Sprite sprite;

	void Initialize();
	void Load();
	void Update(Skeleton& skeleton);
	void HandleEvent(sf::Event& event, Skeleton& skeleton);
	void Draw(sf::RenderWindow& window);
};
