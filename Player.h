/*
 * Player.h
 *
 *  Created on: May 9, 2020
 *      Author: danyal-faheem
 */

#ifndef PLAYER_H_
#define PLAYER_H_
#include <iostream>
#include <string>
using namespace std;
class Player {
protected:
	string name;
	int score, moves, level, highscores[4];
public:
	Player();
	Player(string n, int s, int m, int le);
	Player(const Player &other);
	string getname()const;
	void setname(string);
	int getscore()const;
	void setscore(int);
	int getmoves()const;
	void setmoves(int);
	void set(int, int, int);
	int getlevel()const;
	void setlevel(int);
	const int* gethighscores()const;
	void sethighscores(int*);
	void WritetoFile();
	void ReadFromFile();
	//Player operator=(const Player&);
};

#endif /* PLAYER_H_ */
