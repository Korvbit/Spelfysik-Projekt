#include "Arrow.h"
#include "World.h"
#include <cmath>


Arrow::Arrow(sf::Vector2f position, sf::RectangleShape hitbox, float mass, float C)
{
	this->area = 0.0002; //8mm diameter
	this->dragC = 1.6;
	this->realTime = 0;
	this->mass = mass;
	this->C = C;
	this->hitbox = hitbox;
	this->hitbox.setOrigin(this->hitbox.getSize().x * 0.5f, this->hitbox.getSize().y * 0.5f);
	this->setPos(position);
	this->velocity = 0;

	this->firstCalc = true;
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

void Arrow::update(float drawWeight, float gravity, float density, float fps, bool launch,
	float Fx, float efficiency, float bowFactor, float bowMass)
{
	//<!--- Calculate position: Grab data from Bow and World --->

	float time = fps;
	float drawBack = Fx; //<!--- TODO: Make strength an input
	drawBack = drawBack*drawWeight;

	if(this->firstCalc)
	{
		this->velocity = (sqrt((drawBack*efficiency) / (this->mass + bowFactor * bowMass)));
		this->firstCalc = false;
	}

	if (time > 0.017f)
	{
		time = 0.017f;
	}

	float Fd = 0.5 * density * this->area * this->dragC * pow(this->velocity, 2);

	float Vx = (this->velocity) * this->direction.x;
	float Vy = (this->velocity) * this->direction.y;

	float ax = -((Fd*Vx) / (this->mass*this->velocity));
	float ay = -((Fd*Vy) / (this->mass*this->velocity));
	float grav = gravity;

	float newSpeedX = Vx + ax*time;
	float newSpeedY = Vy + (ay*time + grav*time);
	
	this->velocity = sqrt(newSpeedX * newSpeedX + newSpeedY * newSpeedY);

	this->direction = sf::Vector2f(newSpeedX / this->velocity, newSpeedY / this->velocity);

	float alpha = -acos(this->direction.x)*180 / 3.141592f;

	this->setRot(fmod(alpha, 360));

	this->setPos(this->getPos() + sf::Vector2f(newSpeedX, newSpeedY));

	if (this->velocity <= 0)
		this->velocity = 0;

	//printf("Hästighät %f\n", this->velocity);
	
}

void Arrow::setPos(sf::Vector2f pos)
{
	this->hitbox.setPosition(pos);
}

void Arrow::setV(int v)
{
	this->velocity = v;
}
