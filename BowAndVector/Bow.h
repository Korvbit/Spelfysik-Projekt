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
	sf::RectangleShape* getHB();

	void setRot(float rotation);
	void update(float v, sf::Vector2f dir);
	Bow(sf::Vector2f pos, sf::RectangleShape hitbox, float bowFactor = 0.05f, float effectFactor = 0.9f, float kraftigBoge = 0.75f, float mass = 3.0f);
	virtual ~Bow();

private:

	void setPos(sf::Vector2f pos);

	sf::RectangleShape hitbox;

	float kraftigBoge;
	float bowFactor;
	float efficiency;
	float mass;
	float drawWeight;

};

