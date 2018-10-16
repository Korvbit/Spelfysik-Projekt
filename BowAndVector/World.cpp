#include "World.h"

const int W_WIDTH = 800, W_HEIGHT = 600;

World::World()
	: window(sf::VideoMode(W_WIDTH, W_HEIGHT), "BowAndVector!")
{

	//<!--- ööööhh, initialisera struct? Objectlista? --->
	Object target;
	target.pos = sf::Vector2f(0.9f, 0.5f);
	target.hitbox = sf::RectangleShape(sf::Vector2f(0.09f, 0.09f));
	target.hitbox.setFillColor(sf::Color::Green);

	this->objectList[0] = target;
}


World::~World()
{
}

bool World::collisionCheck(int objIndex_1, int objIndex_2)
{


	/* <!---

	if (this->objectList[objIndex_1].hitbox 
	overlaps with this->objectList[objIndex_2].hitbox):
	
	return true;
	
	else:

	---> */

	return false;
}
