#include "World.h"


World::World(sf::RenderWindow &window)
	: gameWindow(window)
{
	this->nrOfObjects = 0;

	//Set target variables
	this->addObject(sf::Vector2f (0.9f, 0.5f), sf::Vector2f(32.0f, 32.0f)); //(Pos, Size)

	//Set bow variables
	this->addObject(sf::Vector2f(0.1f, 0.9f), sf::Vector2f(32.0f, 32.0f));

	//Set arrow variables
	this->addObject(sf::Vector2f(0.1f, 0.8f), sf::Vector2f(32.0f, 32.0f));
}

World::~World()
{
}

void World::drawObjects()
{
	this->gameWindow.clear();

	mouseAim(1);

	for (int i = 0; i < this->nrOfObjects; i++)
	this->render(this->objectList[i].hitbox);  //<!--- TODO: hitbox <= sprite

	this->gameWindow.display();
}

void World::render(sf::Drawable &drawable)
{
	this->gameWindow.draw(drawable);
}

void World::mouseAim(int index)
{
	{
		//this->gameWindow.ConvertCoords(this->mouse.x, this->mouse.y);
	
		//gets obj origin coordinates and mouse coordinates
		sf::Vector2f(objPos) = this->objectList[index].pos;
		this->mouse = sf::Mouse::getPosition(this->gameWindow);

		float mouseAngle = -atan2(mouse.x - objPos.x, mouse.y - objPos.y) * 180 / 3.1415926535; //angle in degrees of rotation

		this->objectList[index].hitbox.setRotation(mouseAngle);
		
	}
}

void World::addObject(sf::Vector2f pos, sf::Vector2f size) //TODO: Add Texture to obj
{
	Object obj;

	obj.pos = pos;
	obj.hitbox.setSize(size);
	obj.hitbox.setOrigin(size.x * 0.5f, size.y * 0.5f);
	obj.hitbox.setPosition(W_WIDTH * obj.pos.x, W_HEIGHT * obj.pos.y);
	obj.hitbox.setFillColor(sf::Color::Green);

	this->objectList[this->nrOfObjects++] = obj;
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
