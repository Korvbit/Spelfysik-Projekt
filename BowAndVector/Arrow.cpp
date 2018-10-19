#include "Arrow.h"
#include "World.h"
#include <cmath>


Arrow::Arrow(sf::Vector2f position, sf::RectangleShape hitbox, float mass, float C)
{
	this->dragC = 1.6;
	this->realTime = 0;
	this->mass = mass;
	this->C = C;
	this->hitbox = hitbox;
	this->hitbox.setOrigin(this->hitbox.getSize().x * 0.5f, this->hitbox.getSize().y * 0.5f);
	this->setPos(position);
	this->velocity = 0;
}


Arrow::~Arrow()
{
}

sf::Vector2f Arrow::getPos()
{
	return this->hitbox.getPosition();
}

sf::RectangleShape* Arrow::getHB()
{
	return &this->hitbox;
}

void Arrow::setDir(sf::Vector2f dir)
{
	this->direction = dir;
}

void Arrow::setRot(float rotation)
{
	this->hitbox.setRotation(rotation);
}

float Arrow::getV()
{
	return this->velocity;
}

sf::Vector2f Arrow::getDir()
{
	return this->direction;
}

void Arrow::update(float fps, bool launch, float Fx, float efficiency, float bowFactor, float bowMass)
{
	//<!--- Calculate position: Grab data from Bow and World --->

	if(launch)
		this->velocity = (sqrt((Fx*efficiency) / (this->mass + bowFactor * bowMass))); //<!--- TEMP division med 60 pga 60 fps

	if (realTime == 0)
	{
		this->v0 = this->velocity;
	}

	float newPos = (this->mass / this->dragC
		* log(2.71828)*((this->v0 * this->dragC) / this->mass * realTime + 1));

	float x = newPos * this->direction.x;

	float y = newPos * this->direction.y;

	this->setPos(sf::Vector2f(W_WIDTH * 0.05f, W_HEIGHT * 0.90f) + sf::Vector2f(x,y));

	float deceleration = -((this->dragC/this->mass)*pow(this->velocity,2)); //TODO: Check if correct lol

	this->velocity -= deceleration;

	this->realTime += fps;

	printf("Current Time: %f, GottaGoFast: %f\n", realTime, velocity);
	
}

void Arrow::setPos(sf::Vector2f pos)
{
	this->hitbox.setPosition(pos);
}
