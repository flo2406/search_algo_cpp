#include "Search.h"

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

			father[i][j] = -3;
		}
	}

	make_maze();
}

void Search::change_in_draw()
{
	if (path.size() >= 2)
	{
		int oldX = path[path.size() - 1].first;
		int oldY = path[path.size() - 1].second;
		_grid[oldY][oldX].setFillColor(Color(90, 90, 90));
		path.pop_back();

		int newX = path[path.size() - 1].first;
		int newY = path[path.size() - 1].second;
		_grid[newY][newX].setFillColor(Color(255, 255, 255));
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


// Find path function //


void Search::find_path()
{
	queue<int> q;
	q.push(xA * ROWS + yA);
	father[yA][xA] = -1;
	bool find = false;
	while (!find)
	{
		if (q.empty())
		{
			cout << "Not possible to find a path" << endl;
			return;
		}

		int val = q.front();
		q.pop();
		int _xA = val / ROWS;
		int _yA = val % ROWS;

		if (_xA == xB && _yA == yB)
			find = true;

		else
		{
			check_case(_xA, _yA, _xA - 1, _yA, q);
			check_case(_xA, _yA, _xA + 1, _yA, q);
			check_case(_xA, _yA, _xA, _yA - 1, q);
			check_case(_xA, _yA, _xA, _yA + 1, q);
		}
	}
	int y = yB;
	int x = xB;
	path.push_back(make_pair(x, y));

	while (father[y][x] != -1)
	{
		int tmpY = y;
		int tmpX = x;
		x = father[tmpY][tmpX] / ROWS;
		y = father[tmpY][tmpX] % ROWS;
		path.push_back(make_pair(x, y));
	}
}

void Search::check_case(int oldX, int oldY, int newX, int newY, queue<int> &q)
{
	if (newX < 0 || newX > ROWS || newY < 0 || newY > COLS)
		return;

	if (father[newY][newX] == -2)
	{
		q.push(newX * ROWS + newY);
		father[newY][newX] = oldX * ROWS + oldY;
	}
}


// Make maze functions //




int random(int max)
{
	static bool first = true;
	if(first)
	{
		srand(time(nullptr));
		first = false;
	}

	return rand() % max;
}

void Search::make_maze()
{
	rec_make_maze(xA, yA);
	this->father[yB][xB] = -2;

	for (int i = 0; i < COLS; i++)
	{
		for (int j = 0; j < ROWS; j++)
		{
			if (father[i][j] == -3)
			{
				_grid[i][j].setFillColor(Color(0, 255,0));
				window->draw(_grid[i][j]);
			}
		}
	}
}

void Search::rec_make_maze(int srcX, int srcY)
{
	father[srcX][srcY] = -2;

	vector<pair<int, int>> neigh;
	check_neighbour(neigh, srcX, srcY);	
	
	if(neigh.size() == 0)
		return;

	int val = random(neigh.size());
	auto res = neigh[val];
	rec_make_maze(res.first, res.second);
	rec_make_maze(srcX, srcY);
}

void Search::check_neighbour(vector<pair<int, int>>& v, int x, int y)
{
	if (check_high(x + 1, y))
		v.push_back(make_pair(x + 1, y));

	if (check_low(x - 1, y))
		v.push_back(make_pair(x - 1, y));

	if (check_right(x, y + 1))
		v.push_back(make_pair(x, y + 1));
	
	if (check_left(x, y - 1))
		v.push_back(make_pair(x, y - 1));
}


bool Search::check_high(int x, int y)
{
	if (x >= COLS || father[x][y] != -3)
		return false;

	if (x + 1 < COLS && father[x + 1][y] != -3)
		return false;

	if (y - 1 >= 0 && father[x][y - 1] != -3)
		return false;

	if (y + 1 < ROWS && father[x][y + 1] != -3)
		return false;

	if (y - 1 >= 0 && x + 1 < COLS && father[x + 1][y - 1] != -3)
		return false;

	if (y + 1 < ROWS && x + 1 < COLS && father[x + 1][y + 1] != -3)
		return false;

	return true;
}

bool Search::check_low(int x, int y)
{
	if (x < 0 || father[x][y] != -3)
		return false;

	if (x - 1 >= 0 && father[x - 1][y] != -3)
		return false;

	if (y - 1 >= 0 && father[x][y - 1] != -3)
		return false;

	if (y + 1 < ROWS && father[x][y + 1] != -3)
		return false;

	if (y - 1 >= 0 && x - 1 >= 0 && father[x - 1][y - 1] != -3)
		return false;

	if (y + 1 < ROWS && x - 1 >= 0 && father[x - 1][y + 1] != -3)
		return false;


	return true;
}

bool Search::check_right(int x, int y)
{
	if (y >= ROWS || father[x][y] != -3)
		return false;

	if (y + 1 < ROWS && father[x][y + 1] != -3)
		return false;

	if (x - 1 >= 0 && father[x - 1][y] != -3)
		return false;

	if (x + 1 < COLS && father[x + 1][y] != -3)
		return false;

	if (x - 1 >= 0 && y + 1 < ROWS && father[x - 1][y + 1] != -3 )
		return false;

	if (x + 1 < COLS && y + 1 < ROWS && father[x + 1][y + 1] != -3)
		return false;

	return true;
}

bool Search::check_left(int x, int y)
{
	if (y < 0 || father[x][y] != -3)
		return false;

	if (y - 1 >= 0 && father[x][y - 1] != -3)
		return false;

	if (x - 1 >= 0 && father[x - 1][y] != -3)
		return false;

	if (x + 1 < COLS && father[x + 1][y] != -3)
		return false;

	if (x - 1 >= 0 && y - 1 >= 0 && father[x - 1][y - 1] != -3)
		return false;

	if (x + 1 < COLS && y - 1 >= 0 && father[x + 1][y - 1] != -3 )
		return false;

	return true;
}