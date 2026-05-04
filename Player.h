#pragma once
#include <SFML/Graphics.hpp>
#include "Skeleton.h" 
#include "Bullet.h"

//struct Bullets
//{
//
//	sf::RectangleShape shape{sf::Vector2f(25, 12)};
//	sf::Vector2f direction;
//};
//class Bullets;

class Player
{
private:
	sf::Texture texture;
	sf::Vector2i size;
	
	int health = 100;
	int xIndex = 0;
	int yIndex = 3;
	int frameTimer = 0;
	int frameDelay = 8;

	bool enemyHit = false;

	/*std::vector<Bullets> bullets;*/
	/*float bulletSpeed = 5.f;*/

	Bullets bullets;
	float playerSpeed = 2.f;
	sf::RectangleShape boundingRectangle;

public:
	sf::Sprite sprite{texture};

	Player() = default;
	~Player() = default;
	void Initialize();
	void Load();
	void Update(Skeleton& skeleton,sf::RenderWindow& window);
	void HandleEvent(const std::optional<sf::Event>& event, Skeleton& skeleton,sf::RenderWindow& window,sf::Clock& clock);
	void Draw(sf::RenderWindow& window,sf::Clock& clock);
};
