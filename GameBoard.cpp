/*
 * GameBoard.cpp
 *
 *  Created on: May 12, 2020
 *      Author: danyal-faheem
 */

#include "GameBoard.h"
#include "Menu.h"
#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include "util.h"
using namespace std;

GameBoard::GameBoard():Player("Danyal Faheem", 0, 20, 1), gems(30) {
	x1 = y1 = time = 0;
	state = false;
	InitRandomizer();
}

GameBoard::GameBoard(int t, bool s) {
	state = s;
	time = t;
	x1 = y1 = 0;
}

GameBoard::GameBoard(const GameBoard &other) {
	// TODO Auto-generated constructor stub
	state = other.state;
	time = other.time;
	//gems = other.gems;
	x1 = y1  = 0;
}

int GameBoard::gettime() const{
	return time;
}

void GameBoard::updatetime(int t) {
	time = t;
}

bool GameBoard::getstate() const{
	return state;
}

void GameBoard::setstate(bool s) {
	state = s;
}

bool GameBoard::isLost() {
	if( moves < 1 and score < 200 * level) {
		profile.set(score, moves, level);
		profile.WritetoFile();
		return true;
	}
	return false;
}

bool GameBoard::isWon() {
	if( moves >= 0 and score >= (200 * level) and level >= 3 ) {
		profile.set(score, moves, level);
		profile.WritetoFile();
		return true;
	}
	return false;
}

void GameBoard::DrawBoard() {
	//Checking for the matching of Gems
	for(int counter = 0; counter < 30; counter++){
		if(counter != 4 and counter != 9 and counter != 3 and counter != 8 and counter != 13){
			isMatch(gems[counter].x, gems[counter].y);
		}
	}
	//Drawing the gameboard itseld
	double index_x = 120, index_y = 450;
	DrawLine(index_x - 30, index_y - 430, 480, index_y - 430, 3, colors[INDIGO]);
	DrawLine(index_x - 30, 20, index_x - 30, 490, 3, colors[INDIGO]);
	for(int counter = 1; counter < 31; counter++){
		gems[counter - 1].DrawGem(index_x, index_y);//Calling function to draw gems
		DrawLine(index_x - 30, index_y + 40, 480, index_y + 40, 3, colors[INDIGO]);
		DrawLine(index_x + 40, 20, index_x + 40, 490, 3, colors[INDIGO]);
		if(counter % 5 == 0 and counter > 0) {
			index_y -= 80;
			index_x = 120;
		}
		else {
			index_x += 80;
		}
	}
	if(score / level <= 200) { //Drawing the Progress bar and its progress as score increases
		DrawLine(35, 200, 35, 400, 3, colors[GREEN_YELLOW]);
		DrawLine(35, 200, 60, 200, 3, colors[GREEN_YELLOW]);
		DrawLine(35, 400, 60, 400, 3, colors[GREEN_YELLOW]);
		DrawLine(60, 200, 60, 400, 3, colors[GREEN_YELLOW]);
		for(int counter = 0; counter < score / level; counter += 10){
			DrawRectangle(37, 205 + counter, 21, 7, colors[ORANGE_RED]);
		}
	}
	//Adding the necessary display of game components
	DrawString(50, 520, "Score = " + Num2Str(score), colors[ROYAL_BLUE]);
	DrawString(250, 520, "Moves = " + Num2Str(moves), colors[HOT_PINK]);
	DrawString(450, 540, "Required", colors[SLATE_GRAY]);
	DrawString(450, 520, "Score = " + Num2Str(200 * level), colors[SLATE_GRAY]);
	DrawString(250, 560, "Level = " + Num2Str(level), colors[FLORAL_WHITE]);
	if(time != 1 and time != 0) {
		gems[time].DrawHint();
	}
}

void GameBoard::SwapGems(double x1, double y1, double x2, double y2) {
	moves--; //Decreasing moves after every swap
	int index1 = 0, index2 = 0;
	for(int counter = 0; counter < 30; counter++){ // Checking if the mouse click lies in the gem boxes
		if(gems[counter].x >= x1 - 50 and gems[counter].x <= x1 + 50 and gems[counter].y >= y1 - 50 and gems[counter].y <= y1 +50){
			index1 = counter;
		}
		if(gems[counter].x >= x2 - 50 and gems[counter].x <= x2 + 50 and gems[counter].y >= y2 - 50 and gems[counter].y <= y2 +50){
			index2 = counter;
		}
	}
	string s = gems[index1].gettype(); // Swapping gems
	gems[index1].settype(gems[index2].gettype());
	gems[index2].settype(s);
	if(isMatch(x2,y2) == false and isMatch(x1,y1) == false){ // Checking if gems match after swapping
		string s = gems[index1].gettype();
		gems[index1].settype(gems[index2].gettype());
		gems[index2].settype(s);
	}
}

bool GameBoard::isMatch(double x, double y) {
	DropGems(); // Checking for cascading gems
	int index = 0;
	for(int counter = 0; counter < 30; counter++) { //Finding the index of the match gem called
		if(gems[counter].x >= x - 50 and gems[counter].x <= x + 50 and gems[counter].y >= y - 50 and gems[counter].y <= y + 50){
			index = counter;
		}
	}
	// Looking for matching gems inside rows or colums
	int counter = 1, count = 1, ycounter = 5, ycount = 5;
	while (true) {
		if(index + counter < 30 and gems[index + counter].gettype() == gems[index].gettype() and gems[index + counter].y == gems[index].y) {
			counter++;
		}
		else if(index - counter > 0 and gems[index - count].gettype() == gems[index].gettype() and gems[index - count].y == gems[index].y) {
			count++;
		}
		else if(index + ycounter < 30 and gems[index + ycounter].gettype() == gems[index].gettype() and gems[index + ycounter].x == gems[index].x) {
			ycounter += 5;
		}
		else if(index - counter > 0 and gems[index - ycount].gettype() == gems[index].gettype() and gems[index - ycount].x == gems[index].x) {
			ycount += 5;
		}
		else {
			break;
		}
	}
	// Counting matching gems and disappearing them while adding score
	//Checking for horizontal matches
	switch(counter) {
	case 1:
		if(count > 2){
			for(int count2 = 0; count2 < count; count2++){
				gems[index - count2].settype("type");
			}
			score += count * 2;
			return true;
		}
		break;
	case 2:
		if(count >= 2){
			gems[index + 1].settype("type");
			score += (count + counter) * 2;
			for(int count2 = 0; count2 < count; count2++){
				gems[index - count2].settype("type");
			}
			return true;
		}
		break;
	case 3:
		if(count >= 2){
			score += (count + counter) * 2;
			for(int count2 = 0; count2 < count; count2++){
				gems[index - count2].settype("type");
			}
		}
		else {
			score += counter * 2;
			gems[index].settype("type");
		}
		gems[index + 1].settype("type");
		gems[index + 2].settype("type");
		return true;
		break;
	case 4:
		if(count >= 2){
			score += (count + counter) * 3;
			for(int count2 = 0; count2 < count; count2++){
				gems[index - count2].settype("type");
			}
		}
		else {
			score += counter * 3;
			gems[index].settype("type");
		}
		gems[index + 1].settype("type");
		gems[index + 2].settype("type");
		gems[index + 3].settype("type");
		return true;
		break;
	case 5:
		if(count >= 2){
			score += (count + counter) * 4;
			for(int count2 = 0; count2 < count; count2++){
				gems[index - count2].settype("type");
			}
		}
		else {
			score += counter * 4;
			gems[index].settype("type");
		}
		gems[index + 1].settype("type");
		gems[index + 2].settype("type");
		gems[index + 3].settype("type");
		gems[index + 4].settype("type");
		return true;
		break;
	default:
		break;
	}
	//Checking for vertical matches
	switch(ycounter) {
	case 5:
		if(ycount > 10){
			score += ((ycount / 5) * 2);
			for(int count2 = 0; count2 < ycount; count2 += 5){
				gems[index - count2].settype("type");
			}
			return true;
		}
		break;
	case 10:
		if(ycount >= 10){
			gems[index + 5].settype("type");
			score += ((ycount / 5) + (ycounter / 5)) * 2;
			for(int count2 = 0; count2 < ycount; count2 += 5){
				gems[index - count2].settype("type");
			}
			return true;
		}
		break;
	case 15:
		if(ycount >= 10){
			score += ((ycount / 5) + (ycounter / 5)) * 2;
			for(int count2 = 0; count2 < ycount; count2 += 5){
				gems[index - count2].settype("type");
			}
		}
		else {
			score += (ycounter / 5) * 2;
			gems[index].settype("type");
		}
		gems[index + 5].settype("type");
		gems[index + 10].settype("type");
		return true;
		break;
	case 20:
		if(ycount >= 10){
			score += ((ycount / 5) + (ycounter / 5)) * 3;
			for(int count2 = 0; count2 < ycount; count2 += 5){
				gems[index - count2].settype("type");
			}
		}
		else {
			score += (ycounter / 5) * 3;
			gems[index].settype("type");
		}
		gems[index + 5].settype("type");
		gems[index + 10].settype("type");
		gems[index + 15].settype("type");
		return true;
		break;
	case 25:
		if(ycount >= 10){
			score += ((ycount / 5) + (ycounter / 5)) * 4;
			for(int count2 = 0; count2 < ycount; count2 += 5){
				gems[index - count2].settype("type");
			}
		}
		else {
			score += (ycounter / 5) * 4;
			gems[index].settype("type");
		}
		gems[index + 5].settype("type");
		gems[index + 10].settype("type");
		gems[index + 15].settype("type");
		gems[index + 20].settype("type");
		return true;
		break;
	default:
		break;
	}
	return false;
}

GameBoard::~GameBoard() {

}

void GameBoard::updatelevel() { //Function to update the level if score has been reached
	if(score / level >= 200) {
		level++;
		score = 0;
		moves = 20;
	}
}

void GameBoard::DropGems() { //Function to drop and subsequently add new gems when rows have been matched and gems disappear
	for(int counter = 0; counter < 30; counter++) {
		if(gems[counter].gettype() == "type" and counter > 4) {
			gems[counter].settype(gems[counter - 5].gettype());
			gems[counter - 5].settype("type");
		}
	}
}

void GameBoard::GiveHint() {
	bool check = false;
	int counter = 0;
	for(; counter < 30; counter++) {
		if(counter < 29 and gems[counter].gettype() == gems[counter + 1].gettype() and gems[counter].y == gems[counter + 1].y) {
			if((counter + 4 < 30 and gems[counter + 4].gettype() == gems[counter].gettype()) or (counter - 6 >= 0 and gems[counter - 6].gettype() == gems[counter].gettype()) or (counter + 3 < 30 and gems[counter + 3].gettype() == gems[counter].gettype() and gems[counter + 3].x == gems[counter].x) or (counter - 3 >= 0 and gems[counter - 3].gettype() == gems[counter].gettype() and gems[counter - 3].x == gems[counter].x) or (counter + 7 < 30 and gems[counter + 7].gettype() == gems[counter].gettype())) {
				check = true;
				break;
			}
		}
		 if(counter < 25 and gems[counter].gettype() == gems[counter + 5].gettype() and gems[counter].x == gems[counter + 5].x) {
			if((counter + 9 < 30 and gems[counter + 9].gettype() == gems[counter].gettype()) or ( counter + 11 < 30 and gems[counter + 11].gettype() == gems[counter].gettype()) or ( counter + 10 < 30 and gems[counter + 10].gettype() == gems[counter].gettype()) or (counter - 4 >= 0 and gems[counter - 4].gettype() == gems[counter].gettype()) or (counter - 6 >= 0 and gems[counter - 6].gettype() == gems[counter].gettype())) {
				break;
			}
		}
		 if(counter < 28 and gems[counter].gettype() == gems[counter + 2].gettype() and gems[counter].y == gems[counter + 2].y) {
			if((counter + 6 < 30 and gems[counter + 6].gettype() == gems[counter].gettype()) or (counter - 4 >= 0 and gems[counter - 4].gettype() == gems[counter].gettype())) {
				check = true;
				break;
			}
		}
		 if(counter < 20 and gems[counter].gettype() == gems[counter + 10].gettype() and gems[counter].x == gems[counter + 10].x) {
			if((counter + 4 < 30 and gems[counter + 4].gettype() == gems[counter].gettype()) or ( counter + 6 < 30 and gems[counter + 6].gettype() == gems[counter].gettype())) {
				check = true;
				break;
			}
		}
	}
	if(check == true) {
		moves--;
		time = counter;
	}
}
