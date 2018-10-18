#pragma once

#include <string>
#include "Arrow.h"
#include "Bow.h"
#include <SFML\Graphics.hpp>

const int W_WIDTH = 800, W_HEIGHT = 600;

struct Object
{
	sf::Vector2f pos;
	std::string type;
	sf::RectangleShape hitbox;
	sf::Texture texture;
};

class World
{
public:
	World(sf::RenderWindow &window, sf::Vector2f BApos, sf::RectangleShape arrowHB, sf::RectangleShape bowHB);
	virtual ~World();
	void drawObjects();
	sf::Vector2i mouse;
	bool Button1;
	bool collisionCheck(int arrow, int objIndex_2);

private:
	sf::RenderWindow &gameWindow;
	struct Object objectList[256];
	int nrOfObjects;
	Arrow arrow;
	Bow bow;

	void mouseAim(int index);
	void mouseBtn1();
	void addObject(sf::Vector2f pos, sf::Vector2f size);
	void render(sf::Drawable &drawable); //Calls draw()
};

