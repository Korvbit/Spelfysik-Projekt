#include "Arrow.h"
#include <cmath>


Arrow::Arrow(sf::Vector2f position, sf::RectangleShape hitbox, float mass, float C)
{
	this->mass = mass;
	this->C = C;
	this->hitbox = hitbox;
	this->hitbox.setOrigin(this->hitbox.getSize().x * 0.5f, this->hitbox.getSize().y * 0.5f);
	//this->setPos(position);
	this->setPos(sf::Vector2f(800 * 0.5f, 600 * 0.5f));
	this->velocity = 0;
}


Arrow::~Arrow()
{
}

sf::Vector2f Arrow::getPos()
{
	return this->hitbox.getPosition();
}

sf::RectangleShape Arrow::getHB()
{
	return this->hitbox;
}

void Arrow::update(bool launch, float Fx, float efficiency, float bowFactor, float bowMass)
{
	//<!--- Calculate position: Grab data from Bow and World --->

	if(launch)
		this->velocity = (sqrt((Fx*efficiency) / (this->mass + bowFactor * bowMass))) / 60; // division med 60 pga 60 fps

	this->setPos(this->getPos() + this->velocity * this->direction);

	float russin = 0;

	this->velocity = this->velocity - russin;
	
}

void Arrow::setPos(sf::Vector2f pos)
{
	this->hitbox.setPosition(pos);
}
