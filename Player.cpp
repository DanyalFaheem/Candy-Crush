/*
* Player.cpp
*
*  Created on: May 9, 2020
*      Author: danyal-faheem
*/

#include "Player.h"
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

Player::Player() {
	// TODO Auto-generated constructor stub
	name = " ";
	moves = score = level = 0;
}

Player::Player(string n, int s, int m, int le) {
	name = n;
	score = s;
	moves = m;
	level = le;
}

Player::Player(const Player &other) {
	// TODO Auto-generated constructor stub
	name = other.name;
	score = other.score;
	moves = other.moves;
	level = other.level;
	for(int counter = 0; counter < 4; counter++){
		highscores[counter] = other.highscores[counter];
	}
}

string Player::getname() const{
	return name;
}

void Player::setname(string n) {
	name = n;
}

int Player::getmoves() const{
	return moves;
}

void Player::setmoves(int m) {
	moves = m;
}

int Player::getlevel() const{
	return level;
}

void Player::setlevel(int l) {
	level = l;
}

const int* Player::gethighscores() const{
	return highscores;
}

void Player::sethighscores(int* h) {
	for(int counter = 0; counter < 4; counter++){
		highscores[counter] = h[counter];
	}
}

int Player::getscore() const{
	return score;
}

void Player::setscore(int s) {
	score = s;
}

void Player::set(int s, int m, int l) {
	score = s;
	moves = m;
	level = l;
	if(score > highscores[3]) {
		highscores[3] = score;
	}
	/*for(int counter = 0; counter < 4; counter++){
		for(int count = 0; count < 3; count++){
			if( highscores[count] < highscores[count + 1]){
				int temp = highscores[count + 1];
				highscores[count + 1] = highscores[count];
				highscores[count] = temp;
 			}
		}
	}*/
}

void Player::WritetoFile() { //Function to write the data to file, called at termination of program
	ofstream file;
	file.open("PlayerProfile.txt");
	file << name << endl << score << endl << moves << endl << level << endl;
	file.close();
	for(int counter = 0; counter < 4; counter++){
		for(int count = 0; count < 3; count++){
			if( highscores[count] < highscores[count + 1]){
				int temp = highscores[count + 1];
				highscores[count + 1] = highscores[count];
				highscores[count] = temp;
 			}
		}
	}
	ofstream file2;
	file2.open("Highscores.txt");
	for(int counter = 0; counter < 4; counter++) {
		file2 << highscores[counter] << endl;
	}
	file2.close();
}

void Player::ReadFromFile() { //Function to read the data from file, called at start of program
	ifstream file;
	string profile[8];
	file.open("PlayerProfile.txt");
	for(int counter = 0; counter < 4; counter++) {
		getline(file, profile[counter]);
	}
	this->name = profile[0];
	int i = stoi(profile[1]), j = stoi(profile[2]), k = stoi(profile[3]);
	file.close();
	ifstream file2;
	file2.open("Highscores.txt");
	for(int counter = 4; counter < 8; counter++) {
		getline(file2,profile[counter]);
	}
	int n = stoi(profile[4]), m = stoi(profile[5]), l = stoi(profile[6]), p = stoi(profile[7]);
	int arr[4] = {n , m , l , p};
	this->set(i , j , k );
	this->sethighscores(arr);
	file2.close();
	return;
}
