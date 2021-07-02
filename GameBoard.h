/*
 * GameBoard.h
 *
 *  Created on: May 12, 2020
 *      Author: danyal-faheem
 */

#ifndef GAMEBOARD_H_
#define GAMEBOARD_H_
#include <iostream>
#include <vector>
#include "Gem.h"
#include "Player.h"
#include "Menu.h"
using namespace std;
class GameBoard : public Player , public Menu {
protected:
	int time;
	bool state;
private:
	vector <Gem> gems;
public:
	double x1, y1;
	GameBoard();
	GameBoard(int, bool);
	GameBoard(const GameBoard &other);
	int gettime()const;
	void updatetime(int);
	bool getstate()const;
	void setstate(bool);
	bool isLost();
	bool isWon();
	void DrawBoard();
	void SwapGems(double,double,double,double);
	bool isMatch(double,double);
	void updatelevel();
	void DropGems();
	void GiveHint();
	~GameBoard();
};

#endif /* GAMEBOARD_H_ */
