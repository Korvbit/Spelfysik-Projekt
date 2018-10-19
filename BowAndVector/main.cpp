#include <SFML\Graphics.hpp>
#include "World.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(W_WIDTH, W_HEIGHT), "BowAndVector");

	sf::Vector2f BApos = sf::Vector2f(W_WIDTH * 0.05f, W_HEIGHT * 0.90f);
	sf::RectangleShape arrowHB(sf::Vector2f(11.0f, 54.0f));
	sf::RectangleShape bowHB(sf::Vector2f(54.0f, 54.0f));

	World world(window, BApos, arrowHB, bowHB);

	window.setFramerateLimit(60);

	sf::Clock clock;
	sf::Time time;

	while (window.isOpen())
	{
		if (world.Button1 == true)
		{
			time = clock.getElapsedTime();
			float currentTime = clock.restart().asSeconds();
			world.fps = time.asSeconds();

			//printf("FPS: %f\n", world.fps);
		}

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