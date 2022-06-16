#pragma once

#include <SFML/Graphics.hpp>
using namespace sf;

class Search
{
	private: 
		static const unsigned int COLS = 20;
		static const unsigned int ROWS = 40;
		
		int xA;
		int yA;
		int xB;
		int yB;

		RenderWindow* window;
		Clock clock;
		RectangleShape _grid[COLS][ROWS];


	public:
		Search(RenderWindow *window, int xA, int yA, int xB, int yB);
		void draw();
		void change_in_draw();
};

