#include "Bow.h"


float Bow::getBow()
{
	return this->bowFactor;
}

float Bow::getEffect()
{
	return this->effectFactor;
}

float Bow::getMass()
{
	return this->mass;
}

float Bow::getDraw()
{
	return this->drawBack;
}

Bow::Bow(float bowFactor, float effectFactor, float mass, float drawBack, sf::Texture bowSprite)
{
	this->bowFactor = bowFactor;
	this->effectFactor = effectFactor;
	this->mass = mass;
	this->drawBack = drawBack;
	this->bowSprite = bowSprite;
}

Bow::~Bow()
{
}
