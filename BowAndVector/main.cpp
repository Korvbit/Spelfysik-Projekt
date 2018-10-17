#include <SFML\Graphics.hpp>
#include "World.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(W_WIDTH, W_HEIGHT), "BowAndVector");

	World world(window); //Overloaded constructor
	//TODO:	Write initiation for Arrow and Bow
	//		Render Arrow and Bow
	//		

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		world.drawObjects();
	}

	return 0;
}