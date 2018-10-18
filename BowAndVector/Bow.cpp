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
	return this->hitbox.getPosition();
}

sf::RectangleShape* Bow::getHB()
{
	return &this->hitbox;
}

void Bow::setRot(float rotation)
{
	this->hitbox.setRotation(rotation);
}

void Bow::update(float v, sf::Vector2f dir)
{
	this->setPos(this->getPos() + v * dir);
}

Bow::Bow(sf::Vector2f pos, sf::RectangleShape hitbox, float bowFactor, float effectFactor, float kraftigBoge, float mass)
{
	this->hitbox = hitbox;
	this->hitbox.setOrigin(this->hitbox.getSize().x * 0.5f, this->hitbox.getSize().y * 0.5f);
	this->bowFactor = bowFactor;
	this->efficiency = effectFactor;
	this->mass = mass;
	this->kraftigBoge = kraftigBoge;
	this->setPos(pos);
}

Bow::~Bow()
{
}

void Bow::setPos(sf::Vector2f pos)
{
	this->hitbox.setPosition(pos);
}
