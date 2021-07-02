/*
 * Menu.h
 *
 *  Created on: May 12, 2020
 *      Author: danyal-faheem
 */

#ifndef MENU_H_
#define MENU_H_
#include <iostream>
#include "Player.h"
using namespace std;
class Menu {
private:
	int state;
public:
	Player profile;
	Menu();
	Menu(bool);
	Menu(const Menu &other);
	void DisplayProfile();
	void DisplayRules();
	void LostMenu();
	void WonMenu();
	void DrawMenu();
	void PauseMenu();
	int getstat()const;
	void setstat(int);
};

#endif /* MENU_H_ */
