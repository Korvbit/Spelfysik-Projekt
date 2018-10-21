#include <SFML\Graphics.hpp>
#include "World.h"
#include <iostream>
#include <Windows.h>

using namespace std;

int main()
{
	char startChoice;
	info input;

	cout << "Welcome to Archery Simulator!" << endl << endl;
	cout << "Please provide information about the world." << endl;
	cout << "Gravity: ";
	cin >> input.worldData.gravity;
	cout << "Atmosphere density: ";
	cin >> input.worldData.density;
	cout << endl << "Please provide information about the bow." << endl;
	cout << "Bow weight: ";
	cin >> input.bowData.weight;
	cout << "Draw weight: ";
	cin >> input.bowData.drawWeight;
	cout << "Bow factor: ";
	cin >> input.bowData.bowFactor;
	cout << "Efficiency: ";
	cin >> input.bowData.efficiency;
	cout << endl << "The simulation is prepared, do you wish to begin? (y/n)" << endl;
	cin >> startChoice;

	if (startChoice == 'y')
	{
		cout << "Starting simulation..." << endl;
		Sleep(1500);

		sf::View view(sf::Vector2f(W_WIDTH*0.5, W_HEIGHT*0.5), sf::Vector2f(W_WIDTH, W_HEIGHT));

		sf::RenderWindow window(sf::VideoMode(W_WIDTH, W_HEIGHT), "BowAndVector");

		sf::Vector2f BApos = sf::Vector2f(54.0f, W_HEIGHT * 0.90f);
		sf::RectangleShape arrowHB(sf::Vector2f(11.0f, 54.0f));
		sf::RectangleShape bowHB(sf::Vector2f(54.0f, 54.0f));
		sf::RectangleShape objHB(sf::Vector2f(54.0f, 54.0f));

		sf::RectangleShape background(sf::Vector2f(W_WIDTH, W_HEIGHT));

		World world(window, BApos, arrowHB, bowHB, objHB, background, input);

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

			world.drawObjects(&view, background);
		}
	}
	

	cout << "Exiting archery simulator...";
	Sleep(1500);

	return 0;
}