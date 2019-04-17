#include <iostream>
#include <Windows.h>
#include <stdio.h>
#include <conio.h>

using namespace std;

bool gameOver;
int width = 30, height = 10, nTail, x, y, fx, fy, ms = 200, score = 0;
int tailX[100], tailY[100];

enum eDir { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDir dir;

void start(){
	gameOver = false;
	x = width / 2;
	y = height / 2;
	fx = rand() % width;
	fy = rand() % height;
}

void draw() {
	system("cls");
	
	for (int i = 0; i <= width+2; i++) cout << '#';
	cout << endl;
	for (int j = 0; j <= height; j++) {
		for (int i = 0; i <= width; i++) {
			if (i == 0) cout << '#';
			if (x == i && y == j) cout << '*';
			else if (fx == i && fy == j) cout << 'o';
			else {
				bool print = false;
				for (int k = 0; k < nTail; k++)
				{
					if (tailX[k] == i && tailY[k] == j) {
						cout << "*";
						print = true;
					}		
				}
				if (!print) cout << ' ';
			}
			if (i == width) cout << '#' << endl;
		}
	}
	for (int i = 0; i <= width+2; i++) cout << '#';
	cout << "SCORE: " << score;
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
	if (x == -1 || x >= width + 1) gameOver = true;
	if (y == -1 || y >= height + 1) gameOver = true;
	if (fx == x && fy == y) {
		nTail++;
		score += 10;
		fx = rand() % width;
		fy = rand() % height;
	}
	for (int i = 0; i < nTail; i++)
		if (tailX[i] == x && tailY[i] == y) gameOver = true;
}

void logic() {
	int 
		prevTX = tailX[0],
		prevTY = tailY[0],
		prevTX2, prevTY2;
	tailX[0] = x;
	tailY[0] = y;
	for (int i = 1; i < nTail; i++)
	{
		prevTX2 = tailX[i];
		prevTY2 = tailY[i];
		tailX[i] = prevTX;
		tailY[i] = prevTY;
		prevTX = prevTX2;
		prevTY = prevTY2;
	}
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
