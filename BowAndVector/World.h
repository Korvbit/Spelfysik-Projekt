#pragma once

#include <string>
#include "Arrow.h"
#include "Bow.h"
#include <SFML\Graphics.hpp>
#include <cmath>

const int W_WIDTH = 1280, W_HEIGHT = 720;

struct Object
{
	sf::Vector2f pos;
	std::string type;
	sf::RectangleShape hitbox;
	sf::Texture* texture;
};

class World
{
public:
	World(sf::RenderWindow &window, sf::Vector2f BApos, sf::RectangleShape arrowHB, sf::RectangleShape bowHB, sf::RectangleShape objHB, sf::RectangleShape background);
	virtual ~World();
	void drawObjects(sf::View *view, sf::RectangleShape background);
	sf::Vector2i mouse;
	float fps;
	bool Button1;
	bool collisionCheck(int objIndex_2);

	//<!---TEMP

private:
	sf::RenderWindow &gameWindow;
	sf::Sprite bgRec1;
	sf::Texture arrowSprite;
	sf::Texture bowSprite;
	sf::Texture objSprite;
	sf::Texture bg1;

	struct Object objectList[256];
	int nrOfObjects;
	Arrow arrow;
	Bow bow;
	bool loaded;
	bool repulsion;
	bool endGame;
	float gravity;
	float density;

	void loadTextures(sf::RectangleShape *background);
	void trajectoryRot();
	void mouseAim(int index);
	void mouseBtn1();
	void mouseBtn2(sf::View *view);
	void setTexture(Object object);
	void addObject(sf::RectangleShape *HB);
	void render(sf::Drawable &drawable); //Calls draw()
};

