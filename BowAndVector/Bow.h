#pragma once

#include <SFML\Graphics.hpp>

class Bow
{
public:

	float getBow();
	float getEffect();
	float getMass();
	float getDraw();

	Bow(float bowFactor, float effectFactor, float mass, float drawBack, sf::Texture bowSprite);
	virtual ~Bow();

private:

	sf::Texture bowSprite;

	float bowFactor;
	float effectFactor;
	float mass;
	float drawBack;

};

