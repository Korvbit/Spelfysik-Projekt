#include "World.h"


World::World(sf::RenderWindow &window, sf::Vector2f BApos, sf::RectangleShape arrowHB, sf::RectangleShape bowHB, sf::Texture arrowSprite, sf::Texture bowSprite)
	: gameWindow(window), arrow(BApos, arrowHB, arrowSprite), bow(BApos, bowHB, bowSprite)
{
	this->nrOfObjects = 0;
	this->Button1 = false;

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

	if (this->Button1 == false)
	{
		mouseAim(1);
		mouseBtn1(); // true if button has been pressed
	}
	else
	{							
		this->arrow.update(	this->Button1,
							this->bow.getKraftigBoge(),
							this->bow.getEfficiency(),
							this->bow.getBowFactor(),
							this->bow.getMass());
	}

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
	this->gameWindow.mapPixelToCoords(this->mouse);
	
	//gets obj origin coordinates and mouse coordinates
	sf::Vector2f(objPos) = this->bow.getPos();
	this->mouse = sf::Mouse::getPosition(this->gameWindow);
		
	printf("Pos: %d , %d \n",mouse.x, mouse.y);

	float mouseAngle = -atan2(mouse.x - objPos.x, mouse.y - objPos.y) * 180 / 3.14159; //angle in degrees of rotation

	printf("Angelel: %f \n", fmod(mouseAngle, 360));

	this->bow.setRot(fmod(mouseAngle, 360));
}

void World::mouseBtn1()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) == true)
	{
		this->Button1 = true;
		printf("0");
	}
}

void World::addObject(sf::Vector2f pos, sf::Vector2f size) //TODO: Add Texture to obj
{
	Object obj;

	obj.pos = sf::Vector2f(W_WIDTH * pos.x, W_HEIGHT * pos.y);
	obj.hitbox.setSize(size);
	obj.hitbox.setOrigin(size.x * 0.5f, size.y * 0.5f);
	obj.hitbox.setPosition(obj.pos);
	obj.hitbox.setFillColor(sf::Color::Green);

	this->objectList[this->nrOfObjects++] = obj;
}

bool World::collisionCheck(int arrow, int objIndex_2)
{
	/* <!---

	if (this->objectList[objIndex_1].hitbox 
	overlaps with this->objectList[objIndex_2].hitbox):
	
	return true;
	
	else:

	---> */


	return false;
}
