#ifndef ARROW_H
#define ARROW_H

#include <SFML\Graphics.hpp>

class Arrow
{
public:
	Arrow(sf::Vector2f position, sf::RectangleShape hitbox, float mass = 0.045, float C = 1);
	virtual ~Arrow();
	sf::Vector2f getPos();
	sf::RectangleShape* getHB();
	bool firstCalc;
	float totalTime;

	void setDir(sf::Vector2f dir);
	void setRot(float rotation);
	void setPos(sf::Vector2f pos);
	void setV(int v);

	float getV();
	sf::Vector2f getDir();
	
	void update(float drawWeight, float gravity, float density, float fps, bool launch,
		float Fx, float efficiency, float bowFactor, float bowMass);
private:

	float area;
	float v0;
	float mass;
	float C;
	float dragC;
	sf::RectangleShape hitbox;
	float velocity;
	sf::Vector2f direction;
};

#endif