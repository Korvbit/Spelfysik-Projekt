#pragma once

#include <SFML\Graphics.hpp>

class Arrow
{
public:
	Arrow(float position, float mass, float C, sf::Texture arrowSprite);
	virtual ~Arrow();

	float update();
private:
	sf::Texture arrowSprite;

	float position;
	float mass;
	float C;
};

