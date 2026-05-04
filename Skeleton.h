#pragma once
#include <SFML/Graphics.hpp>

class Skeleton
{
private:
	sf::Texture texture;
	sf::Vector2i size;
	sf::RectangleShape boundingRectangle;
	int xIndex_ = 0;
	int yIndex_ = 2;

public:
	sf::Sprite sprite{texture};

	Skeleton() = default;
	~Skeleton() = default;
	void Initialize();
	void Load();
	void Update();
	void Draw(sf::RenderWindow& window);
};