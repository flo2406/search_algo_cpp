#include "Search.h"
#include <iostream>

using namespace std;

int main() {
	int xA, yA, xB, yB;
	
	cout << "A row : ";
	cin >> yA;

	cout << "A column : ";
	cin >> xA;

	cout << "B row : ";
	cin >> yB;

	cout << "B column : ";
	cin >> xB;

	RenderWindow window(sf::VideoMode(1600, 800), "Search algo");
	window.setFramerateLimit(60);
	Search s(&window, xA - 1, yA - 1, xB - 1, yB - 1);
	window.display();

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}
		s.draw();
	}

	return 0;
}