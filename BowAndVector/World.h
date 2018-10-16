#pragma once

#include <string>
#include <SFML\Graphics.hpp>


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
	World();
	virtual ~World();

	bool collisionCheck(int objIndex_1, int objIndex_2);

private:
	sf::RenderWindow window;

	struct Object objectList[256];
	int nrOfObjects;
};

