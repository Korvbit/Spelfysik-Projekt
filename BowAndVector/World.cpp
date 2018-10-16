#include "World.h"


World::World(sf::RenderWindow &window)
	: gameWindow(window)
{
	Object target;
	target.pos = sf::Vector2f(0.9f, 0.5f);
	target.hitbox.setSize(sf::Vector2f(32.0f, 32.0f));
	target.hitbox.setPosition(W_WIDTH*target.pos.x, W_HEIGHT*target.pos.y);
	target.hitbox.setFillColor(sf::Color::Green);

	this->objectList[0] = target;
}


World::~World()
{
}

void World::drawObject(int index)
{
	this->render(this->objectList[index].hitbox);  //<!--- TODO: hitbox <= sprite
}

void World::render(sf::Drawable &drawable)
{
	this->gameWindow.clear();
	this->gameWindow.draw(drawable);
	this->gameWindow.display();
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
