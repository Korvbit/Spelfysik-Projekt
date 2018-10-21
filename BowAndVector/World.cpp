#include "World.h"


World::World(sf::RenderWindow &window, sf::Vector2f BApos, sf::RectangleShape arrowHB, sf::RectangleShape bowHB)
	: gameWindow(window), arrow(BApos, arrowHB), bow(BApos, bowHB)
{
	this->nrOfObjects = 0;
	this->density = 1.225;//<!--- TODO: Input based
	this->gravity = 9.82; //<!--- TODO: ^
	this->Button1 = false;
	this->loaded = false;
	this->repulsion = false;
	this->endGame = false;
	this->fps = 0;

	//Set Object variables
	this->addObject(sf::Vector2f (0.9f, 0.5f), sf::Vector2f(54.0f, 54.0f)); //(Pos, Size)
}

World::~World()
{
}

void World::drawObjects()
{

	this->gameWindow.clear();

	if (this->endGame == false)
	{
		if (this->Button1 == false)
		{
			mouseAim(1);
			mouseBtn1(); // true if button has been pressed
		}
		else
		{
			this->arrow.update(this->gravity,
				this->density,
				this->fps,
				this->Button1,
				this->bow.getKraftigBoge(),
				this->bow.getEfficiency(),
				this->bow.getBowFactor(),
				this->bow.getMass());

			trajectoryRot();

			if (this->repulsion == true)
				this->bow.update(this->arrow.getV() / 2, -this->arrow.getDir()); //<!--- TODO: Half speed is not dependant on mass

			
		}
	}

	mouseBtn2(); //Resets arrow

	sf::Vector2f arrowPos(this->arrow.getPos());
	//printf("Arrow X: %f, Y: %f\n", arrowPos.x, arrowPos.y);
		
	/*sf::Vertex line[] =
	{
		sf::Vertex(this->arrow.getPos()),
		sf::Vertex(this->arrow.getPos() + this->arrow.getDir()*(float)100)
	};

	this->gameWindow.draw(line, 2, sf::Lines);
	*/

	sf::Image imageBow, imageArrow, imageObj;
	
	if (this->loaded == false)
	{
		if (!imageBow.loadFromFile("Bow_01.png"))
			printf("Error: File could not be loaded. :-(\n");
		this->bowSprite.loadFromImage(imageBow);

		sf::RectangleShape *bowPtr = bow.getHB();
		bowPtr->setTexture(&bowSprite);

		if (!imageArrow.loadFromFile("Arrow_01.png"))
			printf("Error: File could not be loaded. :-(\n");
		this->arrowSprite.loadFromImage(imageArrow);

		sf::RectangleShape *arrowPtr = arrow.getHB();
		arrowPtr->setTexture(&arrowSprite);

		if (!imageObj.loadFromFile("Object_01.png"))
			printf("Error: File could not be loaded. :-(\n");
		this->objSprite.loadFromImage(imageObj);

		this->loaded = true;
	}

	this->render(*this->bow.getHB());

	this->render(*this->arrow.getHB());

	for (int i = 0; i < this->nrOfObjects; i++)
	{

		this->render(this->objectList[i].hitbox);  //<!--- TODO: hitbox <= sprite
		if (collisionCheck(i))
		{
			this->arrow.setV(0);
			this->endGame = true;
		}

	}

	this->gameWindow.display();
}

void World::render(sf::Drawable &drawable)
{
	this->gameWindow.draw(drawable);
}

void World::trajectoryRot()
{
	float mouseAngle = -atan2(this->arrow.getPos().x+this->arrow.getDir().x - this->arrow.getPos().x,
		this->arrow.getPos().y+this->arrow.getDir().y - this->arrow.getPos().y) * 
		180 / 3.14159; //angle in degrees of rotation

	float finalAngle = fmod(mouseAngle, 360);

	this->arrow.setRot(mouseAngle);

	//printf("\n\nRot: %f\n\n", mouseAngle);
}

void World::mouseAim(int index)
{
	this->gameWindow.mapPixelToCoords(this->mouse);
	
	//gets obj origin coordinates and mouse coordinates
	sf::Vector2f(objPos) = this->bow.getPos();
	this->mouse = sf::Mouse::getPosition(this->gameWindow);

	float mouseAngle = -atan2(mouse.x - objPos.x, mouse.y - objPos.y) * 180 / 3.14159; //angle in degrees of rotation

	float finalAngle = fmod(mouseAngle, 360);

	//printf("mouseAngle: %f\n", finalAngle);

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

void World::mouseBtn2()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Right) == true)
	{
		this->arrow.setPos((sf::Vector2f(W_WIDTH * 0.05f, W_HEIGHT * 0.90f)));
		this->Button1 = false;
		this->arrow.firstCalc = true;
		this->endGame = false;
	}
}

void World::setTexture(Object object)
{
	object.hitbox.setTexture(&objSprite);
}

void World::addObject(sf::Vector2f pos, sf::Vector2f size) //TODO: Add Texture to obj
{
	Object obj;

	sf::RectangleShape *objPtr = &obj.hitbox;

	obj.pos = sf::Vector2f(W_WIDTH * pos.x, W_HEIGHT * pos.y);
	obj.hitbox.setSize(size);
	obj.hitbox.setOrigin(size.x * 0.5f, size.y * 0.5f);
	obj.hitbox.setPosition(obj.pos);
	obj.texture = this->objSprite;
	obj.hitbox.setTexture(&obj.texture);

	this->objectList[this->nrOfObjects++] = obj;
}

bool World::collisionCheck(int objIndex_2)
{
	if (this->arrow.getHB()->getGlobalBounds().intersects(this->objectList[objIndex_2].hitbox.getGlobalBounds()) == true) //Checks intersection between getGlobalBounds() functions
	{
		return true; //intersect
	}
	else
	{
		return false; //!intersect
	}
}
