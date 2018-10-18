#pragma once

#include <SFML\Graphics.hpp>

class Bow
{
public:

	float getBowFactor();
	float getEfficiency();
	float getMass();
	float getKraftigBoge();
	sf::Vector2f getPos();
	sf::RectangleShape getHB();

	void setRot(float rotation);

	Bow(sf::Vector2f pos, sf::RectangleShape hitbox, float bowFactor = 1, float effectFactor = 1, float kraftigBoge = 1, float mass = 1);
	virtual ~Bow();

private:

	void setPos(sf::Vector2f pos);

	sf::RectangleShape hitbox;

	float kraftigBoge;
	float bowFactor;
	float efficiency;
	float mass;

};

