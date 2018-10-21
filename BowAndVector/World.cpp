#include "World.h"


World::World(sf::RenderWindow &window, sf::Vector2f BApos, sf::RectangleShape arrowHB, sf::RectangleShape bowHB, sf::RectangleShape objHB, sf::RectangleShape background, info input)
	: gameWindow(window), arrow(BApos, arrowHB), bow(BApos, bowHB, input.bowData)
{
	this->nrOfObjects = 0;
	this->density = input.worldData.density;
	this->gravity = input.worldData.gravity;
	this->Button1 = false;
	this->loaded = false;
	this->repulsion = false;
	this->endGame = false;
	this->fps = 0;

	//Set Object variables
	objHB.setPosition(W_WIDTH * 0.9f, W_HEIGHT * 0.5f);
	objHB.setOrigin(objHB.getSize().x * 0.5f, objHB.getSize().y * 0.5f);
	this->addObject(&objHB); //(Pos, Size)

	for (int i = 0; i < 255; i++)
	{
		objHB.setPosition((W_WIDTH * 0.0f)+(54*(i)), W_HEIGHT * 1.0f);
		objHB.setOrigin(objHB.getSize().x * 0.5f, objHB.getSize().y * 0.5f);
		this->addObject(&objHB); //(Pos, Size)
	}

	sf::Sprite *ptr = &this->bgRec1;
	bgRec1.setPosition(0, 0);
	sf::Vector2i *ptr1 = &sf::Vector2i(928*15, (int)W_HEIGHT);
	sf::Vector2i *ptr2 = &sf::Vector2i(0, 0);
	ptr->setTextureRect(sf::IntRect(*ptr2, *ptr1));
}

World::~World()
{
}

void World::drawObjects(sf::View *view, sf::RectangleShape background)
{
	this->gameWindow.clear();

	this->loadTextures(&background);

	background.setPosition(W_WIDTH*0.5f, W_HEIGHT*0.5f);

	this->render(this->bgRec1);

	if (this->endGame == false)
	{
		if (this->Button1 == false)
		{
			mouseAim(1);
			mouseBtn1(); // true if button has been pressed
		}
		else
		{
			this->arrow.update(	this->bow.getDraw(), 
								this->gravity,
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

			if (this->arrow.getPos().x > W_WIDTH*0.49)
			{
				float delta = this->arrow.getPos().x - view->getCenter().x;
				if (delta > 54)
					delta = 54;

				view->move(delta, 0.0f);
				gameWindow.setView(*view);
			}

			/*realSpeed = this->arrow.getV() * 72.0f;
			printf("Speed: %f m/s\n", realSpeed);*/
		}
	}

	mouseBtn2(view); //Resets arrow

	sf::Vector2f arrowPos(this->arrow.getPos());
	//printf("Arrow X: %f, Y: %f\n", arrowPos.x, arrowPos.y);
		
	/*sf::Vertex line[] =
	{
		sf::Vertex(this->arrow.getPos()),
		sf::Vertex(this->arrow.getPos() + this->arrow.getDir()*(float)100)
	};

	this->gameWindow.draw(line, 2, sf::Lines);
	*/

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

void World::loadTextures(sf::RectangleShape *background)
{
	sf::Image imageBow, imageArrow, imageObj, bg1Obj;

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

		if (!imageObj.loadFromFile("Object_02.png"))
			printf("Error: File could not be loaded. :-(\n");
		this->objSprite.loadFromImage(imageObj);

		if (!bg1Obj.loadFromFile("bgDark.png"))
			printf("Error: File could not be loaded. :-(\n");
		this->bg1.loadFromImage(bg1Obj);

		bg1.setRepeated(true);

		sf::Sprite *bg1Ptr = &this->bgRec1;
		bg1Ptr->setTexture(bg1);

		for (int i = 0; i < this->nrOfObjects; i++)
		{
			sf::RectangleShape *objPtr = &this->objectList[i].hitbox;
			objPtr->setTexture(&objSprite);
		}

		this->loaded = true;
	}
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

	float drawLength = sqrt(dir.x*dir.x + dir.y*dir.y);
	if (drawLength > W_HEIGHT)
		drawLength = W_HEIGHT;
	drawLength /= 360;
	this->bow.setDraw(drawLength);

	dir.x /= sqrt(pow((a), 2.0) + pow(b, 2.0));
	dir.y /= sqrt(pow((a), 2.0) + pow(b, 2.0));

	//printf("Dragloingd: %f", drawLength);

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

void World::mouseBtn2(sf::View *view)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Right) == true)
	{
		this->arrow.setPos((sf::Vector2f(54.0f, W_HEIGHT * 0.90f)));
		this->Button1 = false;
		this->arrow.firstCalc = true;
		this->endGame = false;

		view->setCenter(W_WIDTH * 0.5, W_HEIGHT*0.5);
		gameWindow.setView(*view);
	}
}

void World::setTexture(Object object)
{
	object.hitbox.setTexture(&objSprite);
}

void World::addObject(sf::RectangleShape *HB)
{
	Object obj;
	
	obj.pos = HB->getPosition();
	obj.hitbox = *HB;
	
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
