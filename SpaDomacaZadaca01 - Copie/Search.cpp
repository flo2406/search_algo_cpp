#include "Search.h"
#include <iostream>

using namespace std;

Search::Search(RenderWindow* window, int xA, int yA, int xB, int yB)
{
	this->window = window;
	this->clock = Clock();
	this->xA = xA;
	this->xB = xB;
	this->yA = yA;
	this->yB = yB;

	for (int i = 0; i < COLS; i++)
	{
		for (int j = 0; j < ROWS; j++)
		{
			_grid[i][j] = RectangleShape(Vector2f(36, 36));
			_grid[i][j].setPosition(j * 40 + 2, i * 40 + 2);

			if (yA == i && xA == j)
				_grid[i][j].setFillColor(Color(255, 255, 255));

			else if (yB == i && xB == j)
				_grid[i][j].setFillColor(Color(255, 0, 0));

			else
				_grid[i][j].setFillColor(Color(90, 90, 90));

			window->draw(_grid[i][j]);
		}
	}
}

void Search::change_in_draw()
{
	if (xA < xB)
	{
		_grid[yA][xA].setFillColor(Color(90, 90, 90));
		++xA;
		_grid[yA][xA].setFillColor(Color(255, 255, 255));
		return;
	}

	if (xA > xB)
	{
		_grid[yA][xA].setFillColor(Color(90, 90, 90));
		--xA;
		_grid[yA][xA].setFillColor(Color(255, 255, 255));
		return;
	}

	if (yA < yB)
	{
		_grid[yA][xA].setFillColor(Color(90, 90, 90));
		++yA;
		_grid[yA][xA].setFillColor(Color(255, 255, 255));
		return;
	}

	if (yA > yB)
	{
		_grid[yA][xA].setFillColor(Color(90, 90, 90));
		--yA;
		_grid[yA][xA].setFillColor(Color(255, 255, 255));
		return;
	}
}


void Search::draw()
{
	if (clock.getElapsedTime().asMilliseconds() > 100)
	{
		change_in_draw();

		for (int i = 0; i < COLS; i++)
		{
			for (int j = 0; j < ROWS; j++)
				window->draw(_grid[i][j]);
		}

		window->display();
		clock.restart();
	}
}