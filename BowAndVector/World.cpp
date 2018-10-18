#include "World.h"


World::World(sf::RenderWindow &window, sf::Vector2f BApos, sf::RectangleShape arrowHB, sf::RectangleShape bowHB)
	: gameWindow(window), arrow(BApos, arrowHB), bow(BApos, bowHB)
{
	this->nrOfObjects = 0;
	this->Button1 = false;
	this->loaded = false;
	this->repulsion = true;

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

		if(this->repulsion == true)
		this->bow.update(this->arrow.getV()/2, -this->arrow.getDir()); //<!--- TODO: Half speed is not dependant on mass
	}

	//for (int i = 0; i < this->nrOfObjects; i++)
	//	this->render(this->objectList[i].hitbox);  //<!--- TODO: hitbox <= sprite
	
	sf::Image imageBow, imageArrow;
	sf::RectangleShape *bowPtr, *arrowPtr;
	
	if (this->loaded == false)
	{
		if (!imageBow.loadFromFile("Bow_01.png"))
			printf("Yall fucked up fam\n");
		bowSprite.loadFromImage(imageBow);

		sf::RectangleShape *bowPtr = bow.getHB();
		bowPtr->setTexture(&bowSprite);

		if (!imageArrow.loadFromFile("Arrow_01.png"))
			printf("Yall fucked up fam\n");
		arrowSprite.loadFromImage(imageArrow);

		sf::RectangleShape *arrowPtr = arrow.getHB();
		arrowPtr->setTexture(&arrowSprite);

		this->loaded = true;
	}

	this->render(*this->bow.getHB());

	this->render(*this->arrow.getHB());

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

	float mouseAngle = -atan2(mouse.x - objPos.x, mouse.y - objPos.y) * 180 / 3.14159; //angle in degrees of rotation

	float finalAngle = fmod(mouseAngle, 360);

	//printf("TopKek: %f\n", finalAngle);

	this->bow.setRot(finalAngle);
	this->arrow.setRot(finalAngle);
	
	float a = mouse.x - objPos.x, b = mouse.y - objPos.y;

	sf::Vector2f dir(mouse.x - objPos.x, mouse.y - objPos.y);
	dir.x /= sqrt(pow((a),2.0) + pow(b, 2.0));
	dir.y /= sqrt(pow((a), 2.0) + pow(b, 2.0));

	this->arrow.setDir(dir);
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
