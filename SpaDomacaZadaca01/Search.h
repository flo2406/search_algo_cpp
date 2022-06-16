#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <queue>
#include <iostream>
using namespace sf;
using namespace std;

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

	int father[COLS][ROWS];
	// father[i][j] == -3  => wall
	// father[i][j] == -2  => not visited
	// father[i][j] == -1  => A point (beginning)
	// father[i][j] == number >= 0  => the node visited before is (number/ROWS, number % ROWS)

	vector<pair<int,int>> path;

	void change_in_draw();
	void check_case(int oldX, int oldY, int newX, int newY, queue<int> &q);
	void make_maze();
	void rec_make_maze(int srcX, int srcY);
	void check_neighbour(vector<pair<int, int>>& v, int srcX, int srcY);
	bool check_high(int x, int y);
	bool check_low(int x, int y);
	bool check_right(int x, int y);
	bool check_left(int x, int y);

public:
	Search(RenderWindow* window, int xA, int yA, int xB, int yB);
	void draw();
	void find_path();
	
};

