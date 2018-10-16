#include "Arrow.h"



Arrow::Arrow(float position, float mass, float C, sf::Texture arrowSprite)
{
	this->position = position;
	this->mass = mass;
	this->C = C;
	this->arrowSprite = arrowSprite;
}


Arrow::~Arrow()
{
}

float Arrow::update()
{
	//<!--- Calculate position: Grab data from Bow and World --->

	return this->position;
}
