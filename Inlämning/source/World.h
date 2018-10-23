#ifndef WORLD_H
#define WORLD_H

#include <string>
#include "Arrow.h"
#include "Bow.h"
#include <SFML\Graphics.hpp>
#include <cmath>
#include <iomanip>
#include <iostream>

struct worldInfo {
	float gravity;
	float density;
};

struct info {
	struct worldInfo worldData;
	struct bowInfo bowData;
};

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
	World(sf::RenderWindow &window, sf::Vector2f BApos, sf::RectangleShape arrowHB, sf::RectangleShape bowHB, sf::RectangleShape objHB, sf::RectangleShape background, info input);
	virtual ~World();

	void drawObjects(sf::View *view, sf::RectangleShape background);
	sf::Vector2i mouse;
	float fps;

	bool Button1;
	bool collisionCheck(int objIndex_2);

	std::string distance;
	std::string drawback;
	std::string speed;

private:
	sf::RenderWindow &gameWindow;
	sf::Sprite bgRec1;
	sf::Texture arrowSprite;
	sf::Texture bowSprite;
	sf::Texture objSprite;
	sf::Texture bg1;
	sf::Font font;
	sf::Text distance_Text;//Displays distance travelled
	sf::Text drawback_Text;//Displays length drawn
	sf::Text speed_Text; //Displays arrows speed

	struct Object objectList[512];
	int nrOfObjects;
	Arrow arrow;
	Bow bow;
	bool loaded;
	bool repulsion;
	bool endGame;
	float gravity;
	float density;
	float realSpeed;
	float lastSpeed;

	void draw_speed();
	void draw_lastSpeed();
	void draw_drawLength();
	void loadTextures(sf::RectangleShape *background);
	void trajectoryRot();
	void mouseAim(int index);
	void mouseBtn1();
	void mouseBtn2(sf::View *view);
	void setTexture(Object object);
	void addObject(sf::RectangleShape *HB);
	void render(sf::Drawable &drawable); //Calls draw()
};

#endif