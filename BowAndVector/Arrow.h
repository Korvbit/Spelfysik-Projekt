#pragma once

#include <SFML\Graphics.hpp>

class Arrow
{
public:
	Arrow(sf::Vector2f position, sf::RectangleShape hitbox, float mass = 1, float C = 1);
	virtual ~Arrow();
	sf::Vector2f getPos();
	sf::RectangleShape getHB();

	void update(bool launch, float Fx, float efficiency, float bowFactor, float bowMass);
private:
	void setPos(sf::Vector2f pos);

	float mass;
	float C;
	sf::RectangleShape hitbox;
	float velocity;
	sf::Vector2f direction;
};