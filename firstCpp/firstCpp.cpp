#include <iostream>
#include <Windows.h>
#include <conio.h>

using namespace std;

bool gameOver;
int width = 30, height = 10, x, y, fx, fy, ms = 300, score = 0;

enum eDir { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDir dir;

void start(){
	gameOver = false;
	x = width / 2;
	y = height / 2;
	fx = rand() % width;
	fy = rand() % height;
}

string direction() {
	string v = "STOP";
	switch (dir) {
	case LEFT:
		v = 'l';
		break;
	case RIGHT:
		v = 'r';
		break;
	case UP:
		v = 'u';
		break;
	case DOWN:
		v = 'd';
		break;
	}
	return v;
}

void draw() {
	system("cls");
	
	for (int i = 0; i <= width+2; i++) {
		cout << '#';
	}
	cout << endl;
	
	for (int j = 0; j <= height; j++) {
		for (int i = 0; i <= width; i++) {
			if (i == 0)
				cout << '#';
			
			if (x == i && y == j)
				cout << 'O';
			else if (fx == i && fy == j)
				cout << '*';
			else
				cout << ' ';

			if (i == width)
				cout << '#' << endl;
		}
	}
	for (int i = 0; i <= width+2; i++)
		cout << '#';
	cout << 
		endl << 
		"DIR: " <<
		direction() << 
		" | SCORE: " << 
		score;
	Sleep(ms);
}

void input() {
	if (_kbhit()) {
		switch (_getch())
		{
		case 'a':
			dir = LEFT;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'w':
			dir = UP;
			break;
		case 'q':
			gameOver = true;
			break;
		}
	}
}

void hit() {
	if (x == -1 || x >= width + 1) {	
		gameOver = true;
	}
	if (y == -1 || y >= height + 1) {
		gameOver = true;
	}
	if (fx == x && fy == y) {
		score++;
		fx = rand() % width;
		fy = rand() % height;
	}
}

void logic() {
	switch (dir)
	{
	case LEFT:
		x--;
		hit();
		break;
	case RIGHT:
		x++;
		hit();
		break;
	case UP:
		y--;
		hit();
		break;
	case DOWN:
		y++;
		hit();
		break;
	}
}

int main()
{
	start();
	while (!gameOver) {
		draw();
		input();
		logic();
	}
}
