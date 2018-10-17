#pragma once

#include <SFML\Graphics.hpp>

class Arrow
{
public:
	Arrow(sf::Vector2f position, sf::RectangleShape hitbox, sf::Texture arrowSprite, float mass = 1, float C = 1, float length = 2);
	virtual ~Arrow();

	void update(bool launch, float Fx, float efficiency, float bowFactor, float bowMass);
private:
	sf::Texture arrowSprite;

	sf::Vector2f position;
	float mass;
	float C;
	float length;
	sf::RectangleShape hitbox;
	float velocity;
	sf::Vector2f direction;
};