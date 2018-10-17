#pragma once

#include <string>
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
	World(sf::RenderWindow &window);
	virtual ~World();
	void drawObjects();
	sf::Vector2i mouse;
	bool Button1;
	bool collisionCheck(int objIndex_1, int objIndex_2);

private:
	sf::RenderWindow &gameWindow;
	struct Object objectList[256];
	int nrOfObjects;

	void mouseAim(int index);
	void mouseBtn1();
	void addObject(sf::Vector2f pos, sf::Vector2f size);
	void render(sf::Drawable &drawable); //Calls draw()
};

