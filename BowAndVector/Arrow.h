#pragma once

#include <SFML\Graphics.hpp>

class Arrow
{
public:
	Arrow(sf::Vector2f position, sf::RectangleShape hitbox, float mass = 0.045, float C = 1);
	virtual ~Arrow();
	sf::Vector2f getPos();
	sf::RectangleShape* getHB();

	void setDir(sf::Vector2f dir);
	void setRot(float rotation);

	float getV();
	sf::Vector2f getDir();

	void update(float fps, bool launch, float Fx, float efficiency, float bowFactor, float bowMass);
private:
	void setPos(sf::Vector2f pos);

	float realTime;
	float v0;
	float mass;
	float C;
	float dragC;
	sf::RectangleShape hitbox;
	float velocity;
	sf::Vector2f direction;
};