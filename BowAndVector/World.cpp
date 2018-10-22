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
	this->lastSpeed = 0;

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

	objHB.setPosition(5040, 648);
	objHB.setOrigin(objHB.getSize().x * 0.5f, objHB.getSize().y * 0.5f);
	this->addObject(&objHB); //(Pos, Size)

	sf::Sprite *ptr = &this->bgRec1;
	bgRec1.setPosition(0, 0);
	sf::Vector2i *ptr1 = &sf::Vector2i(928*15, (int)W_HEIGHT);
	sf::Vector2i *ptr2 = &sf::Vector2i(0, 0);
	ptr->setTextureRect(sf::IntRect(*ptr2, *ptr1));

	this->loadTextures(&background);
}

World::~World()
{
}

void World::drawObjects(sf::View *view, sf::RectangleShape background)
{
	this->gameWindow.clear();

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
			draw_speed();

			this->arrow.update(	this->bow.getDraw(), 
								this->gravity,
								this->density,
								this->fps,
								this->Button1,
								this->bow.getdraw_Back(),
								this->bow.getEfficiency(),
								this->bow.getBowFactor(),
								this->bow.getMass());

			printf("Velocity: %f m/s\n", this->arrow.getV());

			trajectoryRot();
		}
	}

	draw_drawLength();

	if (this->arrow.getPos().x > W_WIDTH*0.49)
	{
		float delta = this->arrow.getPos().x - view->getCenter().x;
		/*if (delta > 54)
			delta = 54; //spdCap*/

		view->move(delta, 0.0f);
		gameWindow.setView(*view);
	}

	mouseBtn2(view); //Resets simulation

	this->render(*this->bow.getHB());

	this->render(*this->arrow.getHB());

	for (int i = 0; i < this->nrOfObjects; i++)
	{

		this->render(this->objectList[i].hitbox);
		if (collisionCheck(i))
		{
			draw_lastSpeed();

			if (endGame == false)
				this->distance = std::to_string((this->arrow.getPos().x - 54.0f) / 72.0f) + "m"; //Conversion factor based on size of arrow
				this->distance_Text.setString(this->distance);
				this->distance_Text.setOrigin(this->distance_Text.getGlobalBounds().width*0.5, this->distance_Text.getGlobalBounds().height*0.5);
				this->distance_Text.setPosition(sf::Vector2f(view->getCenter().x, view->getCenter().y-(0.25*W_HEIGHT)));
				this->gameWindow.draw(this->distance_Text);

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

void World::draw_speed()
{
	float v = this->arrow.getV();

	this->speed = std::to_string(this->arrow.getV()) + "m/s"; //Conversion factor based on size of arrow
	this->lastSpeed = this->arrow.getV();
	this->speed_Text.setString(this->speed);
	this->speed_Text.setScale(sf::Vector2f(0.5f, 0.5f));
	this->speed_Text.setOrigin(this->speed_Text.getGlobalBounds().width*0.25, this->speed_Text.getGlobalBounds().height*0.25);
	this->speed_Text.setPosition(sf::Vector2f(this->arrow.getPos().x, this->arrow.getPos().y - 54));

	this->gameWindow.draw(this->speed_Text);
	
}

void World::draw_lastSpeed()
{
	this->speed_Text.setString(std::to_string(this->lastSpeed) + "m/s");
	this->gameWindow.draw(this->speed_Text);
}

void World::draw_drawLength()
{
	this->drawback = std::to_string(this->bow.getdraw_Back()) + "m"; //Conversion factor based on size of arrow
	this->drawback_Text.setString(this->drawback);
	this->drawback_Text.setScale(sf::Vector2f(0.5f, 0.5f));
	this->drawback_Text.setOrigin(this->drawback_Text.getGlobalBounds().width*0.5, this->drawback_Text.getGlobalBounds().height*0.5);
	this->drawback_Text.setPosition(sf::Vector2f(54, 621 - (this->drawback_Text.getGlobalBounds().height)*2));
	this->gameWindow.draw(this->drawback_Text);
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

		if(!this->font.loadFromFile("LemonMilklight.otf"))
			printf("Error: File could not be loaded. :-(\n");

		this->distance_Text.setFont(this->font);
		this->drawback_Text.setFont(this->font);
		this->speed_Text.setFont(this->font);

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
}

void World::mouseAim(int index)
{
	this->gameWindow.mapPixelToCoords(this->mouse);
	
	//gets obj origin coordinates and mouse coordinates
	sf::Vector2f(objPos) = this->bow.getPos();
	this->mouse = sf::Mouse::getPosition(this->gameWindow);

	float mouseAngle = -atan2(mouse.x - objPos.x, mouse.y - objPos.y) * 180 / 3.14159; //angle in degrees of rotation

	float finalAngle = fmod(mouseAngle, 360);

	this->bow.setRot(finalAngle);
	this->arrow.setRot(finalAngle);
	
	float a = mouse.x - objPos.x, b = mouse.y - objPos.y;

	sf::Vector2f dir(mouse.x - objPos.x, mouse.y - objPos.y);

	float drawLength = sqrt(dir.x*dir.x + dir.y*dir.y);

	if (drawLength > 648)
		drawLength = 648;

	drawLength /= 432; //Maximum draw length 1,5m
	this->bow.setDraw(drawLength);

	dir.x /= sqrt(pow((a), 2.0) + pow(b, 2.0));
	dir.y /= sqrt(pow((a), 2.0) + pow(b, 2.0));

	//printf("Drawback: %f", drawLength);

	//printf("Drawlength: %f\n", drawLength);


	this->arrow.setDir(dir);
}

void World::mouseBtn1()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) == true)
	{
		this->Button1 = true;
	}
}

void World::mouseBtn2(sf::View *view)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Right) == true)
	{
		this->arrow.setPos((sf::Vector2f(54.0f, W_HEIGHT * 0.90f)));
		this->Button1 = false;
		this->arrow.firstCalc = true;
		this->arrow.totalTime = 0;
		this->endGame = false;

		view->setCenter(W_WIDTH * 0.5, W_HEIGHT*0.5);
		gameWindow.setView(*view);

		system("cls");
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
		return false; //no intersect
	}
}
