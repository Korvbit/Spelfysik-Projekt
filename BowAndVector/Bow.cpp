#include "Bow.h"


float Bow::getDraw()
{
	return this->drawWeight;
}

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

void Bow::setDraw(float drawLength)
{
	this->kraftigBoge = drawLength;
}

void Bow::setRot(float rotation)
{
	this->hitbox.setRotation(rotation);
}

void Bow::update(float v, sf::Vector2f dir)
{
	this->setPos(this->getPos() + v * dir);
}

Bow::Bow(sf::Vector2f pos, sf::RectangleShape hitbox, bowInfo input)
{
	this->hitbox = hitbox;
	this->hitbox.setOrigin(this->hitbox.getSize().x * 0.5f, this->hitbox.getSize().y * 0.5f);
	this->bowFactor = input.bowFactor;
	this->efficiency = input.efficiency;
	this->mass = input.weight;
	this->kraftigBoge = 0.75f;
	this->setPos(pos);
	this->drawWeight = input.drawWeight;
}

Bow::~Bow()
{
}

void Bow::setPos(sf::Vector2f pos)
{
	this->hitbox.setPosition(pos);
}
