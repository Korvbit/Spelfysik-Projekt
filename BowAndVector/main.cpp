#include <SFML\Graphics.hpp>
#include "World.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(W_WIDTH, W_HEIGHT), "BowAndVector");

	World myWorld(window); //Overloaded constructor

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		myWorld.drawObject(0);
	}

	return 0;
}