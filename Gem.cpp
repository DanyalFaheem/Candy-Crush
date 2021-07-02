/*
 * Gem.cpp
 *
 *  Created on: May 9, 2020
 *      Author: danyal-faheem
 */

#include "Gem.h"
#include "util.h"
#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
using namespace std;

Gem::Gem() { // Default constructor to randomly assign types to gems
	InitRandomizer();
	string typ[] = {"Triangle", "Circle" , "Rectangle" , "RoundRect", "Square"};
	type = typ[rand() % 5];
	x = y = 0;
}

Gem::Gem(string t) {
	type = t;
	x = y = 0;
}

Gem::Gem(const Gem &other) {
	type = other.type;
	x = other.x;
	y = other.y;
}

void Gem::settype(string t) {
	type = t;
}

string Gem::gettype() const{
	return type;
}

void Gem::DrawGem(double x1, double y1) { // Main function which draws the gems on the board according to the random types assigned in the default constructor
	if(x == 0 and y == 0){
		x = x1;
		y = y1;
	}
	if(type == "Circle") {
		DrawCircle(x, y, 10, colors[RED]);
	}
	else if(type == "Square") {
		DrawSquare(x, y, 18, colors[DARK_GREEN]);
	}
	else if(type == "Rectangle") {
		DrawRectangle(x, y, 12, 18, colors[TURQUOISE]);
	}
	else if(type == "RoundRect") {
		DrawRoundRect(x, y, 18, 12, colors[DEEP_PINK], 10);
	}
	else if(type == "Triangle") {
		DrawTriangle(x + 10, y + 10, x + 10, y - 10, x - 10, y - 10, colors[ORANGE]);
	}
	else {
		string typ[] = {"Triangle", "Circle" , "Rectangle" , "RoundRect", "Square"};
		this->type = typ[rand() % 5];
		this->DrawGem(x1, y1);
	}
}

void Gem::DrawHint() {
	DrawLine(x + 20, y - 20, x + 20, y + 20, 3, colors[ORANGE]);
	DrawLine(x - 20, y - 20, x - 20, y + 20, 3, colors[ORANGE]);
	DrawLine(x - 20, y + 20, x + 20, y + 20, 3, colors[ORANGE]);
	DrawLine(x - 20, y - 20, x + 20, y - 20, 3, colors[ORANGE]);
}
