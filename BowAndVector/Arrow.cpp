#include "Arrow.h"
#include <cmath>


Arrow::Arrow(sf::Vector2f position, sf::RectangleShape hitbox, sf::Texture arrowSprite, float mass, float C, float length)
{
	this->position = position;
	this->mass = mass;
	this->C = C;
	this->arrowSprite = arrowSprite;
	this->length = length;
	this->hitbox = hitbox;
	this->velocity = 0;
}


Arrow::~Arrow()
{
}

void Arrow::update(bool launch, float Fx, float efficiency, float bowFactor, float bowMass)
{
	//<!--- Calculate position: Grab data from Bow and World --->

	if(launch)
		this->velocity = (sqrt((Fx*efficiency) / (this->mass + bowFactor * bowMass))) / 60; // division med 60 pga 60 fps

	this->position += this->velocity * this->direction;

	float russin = 0;

	this->velocity = this->velocity - russin;
	
}
