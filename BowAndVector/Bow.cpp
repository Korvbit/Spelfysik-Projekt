#include "Bow.h"


float Bow::getBowFactor()
{
	return this->bowFactor;
}

float Bow::getEfficiency()
{
	return this->efficiency;
}

float Bow::getMass()
{
	return this->mass;
}

float Bow::getKraftigBoge()
{
	return this->kraftigBoge;
}

sf::Vector2f Bow::getPos()
{
	return this->pos;
}

void Bow::setRot(float rotation)
{
	this->hitbox.setRotation(rotation);
}

Bow::Bow(sf::Vector2f pos, sf::RectangleShape hitbox, sf::Texture bowSprite, float bowFactor, float effectFactor, float kraftigBoge, float mass)
{
	this->hitbox = hitbox;
	this->bowFactor = bowFactor;
	this->efficiency = effectFactor;
	this->mass = mass;
	this->bowSprite = bowSprite;
	this->kraftigBoge = kraftigBoge;
	this->pos = pos;
}

Bow::~Bow()
{
}
