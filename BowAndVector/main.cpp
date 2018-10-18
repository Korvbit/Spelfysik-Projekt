#include <SFML\Graphics.hpp>
#include "World.h"

sf::Texture arrowSprite;
sf::Texture bowSprite;

int main()
{
	sf::RenderWindow window(sf::VideoMode(W_WIDTH, W_HEIGHT), "BowAndVector");

	sf::Image image;

	sf::Vector2f BApos = sf::Vector2f(W_WIDTH * 0.1f, W_HEIGHT * 0.9f);
	sf::RectangleShape arrowHB(sf::Vector2f(11.0f, 54.0f));
	//sf::Texture arrowSprite;
	sf::RectangleShape bowHB(sf::Vector2f(54.0f, 54.0f));
	//sf::Texture bowSprite;

	arrowSprite.loadFromFile("..\Textures\Arrow_01.png");
	arrowHB.setTexture(&arrowSprite);
	arrowHB.setPosition(sf::Vector2f(50, 50));
	//
	/*image.loadFromFile("..\Textures\Arrow_01.png");
	arrowSprite.loadFromImage(image);
	arrowHB.setTexture(&arrowSprite);
	arrowHB.setPosition(sf::Vector2f(50, 50));*/

	///*bowSprite.loadFromFile("..\Textures\Bow_01.png");
	//bowHB.setTexture(&bowSprite);*/

	//image.loadFromFile("..\Textures\Bow_01.png");
	//bowSprite.loadFromImage(image);
	//bowHB.setTexture(&bowSprite);

	/*image.loadFromFile("..\Textures\Arrow_01.png");
	arrowSprite.loadFromImage(image);
	sf::Sprite sprit;
	sprit.setTexture(arrowSprite);*/

	World world(window, BApos, arrowHB, bowHB);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		world.drawObjects();

		window.draw(arrowHB);
	}

	return 0;
}