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

void Arrow::update(float gravity, float density, float fps, bool launch,
	float Fx, float efficiency, float bowFactor, float bowMass)
{
	//<!--- Calculate position: Grab data from Bow and World --->

	float drawBack = Fx;
	drawBack = drawBack*(16.3*gravity);

	if (realTime == 0)
	{
		this->velocity = (sqrt((drawBack*efficiency) / (this->mass + bowFactor * bowMass)));
	}

	this->realTime += fps;

	float Fd = 0.5 * density * this->area * this->dragC * pow(this->velocity, 2);

	float Vx = this->velocity * this->direction.x;
	float Vy = this->velocity * this->direction.y;
	float ax = -((Fd*Vx) / (this->mass*this->velocity));
	float ay = -gravity -((Fd*Vy) / (this->mass*this->velocity));

	//this->velocity += deceleration;
	sf::Vector2f accVec(ax, ay);
	sf::Vector2f at2 = (accVec*pow(realTime, 2));

	sf::Vector2f newV(sf::Vector2f(Vx, Vy)*realTime + (sf::Vector2f(at2*(float)0.5)));

	this->setPos(sf::Vector2f(W_WIDTH * 0.05f, W_HEIGHT * 0.90f) + newV);

	this->velocity = sqrt(pow(newV.x, 2) + pow(newV.y, 2));

	sf::Vector2f newDir = sf::Vector2f(Vx, Vy);
	this->direction.x /= sqrt(pow((newDir.x), 2.0) + pow(newDir.y, 2.0));
	this->direction.y /= sqrt(pow((newDir.x), 2.0) + pow(newDir.y, 2.0));

	if (this->velocity <= 0)
		this->velocity = 0;

	printf("Current Time: %f, V: %f, ax: %f, ay: %f,\n", realTime, this->velocity, ax, ay);
	
}

void Arrow::setPos(sf::Vector2f pos)
{
	this->hitbox.setPosition(pos);
}
