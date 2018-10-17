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

	void setRot(float rotation);

	Bow(sf::Vector2f pos, sf::RectangleShape hitbox, sf::Texture bowSprite, float bowFactor = 1, float effectFactor = 1, float kraftigBoge = 1, float mass = 1);
	virtual ~Bow();

private:

	sf::RectangleShape hitbox;
	sf::Texture bowSprite;

	sf::Vector2f pos;
	float kraftigBoge;
	float bowFactor;
	float efficiency;
	float mass;

};

