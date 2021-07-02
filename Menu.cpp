/*
 * Menu.cpp
 *
 *  Created on: May 12, 2020
 *      Author: danyal-faheem
 */

#include "Menu.h"
#include "util.h"
#include <string>
#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;

Menu::Menu(): profile(){
	// TODO Auto-generated constructor stub
	state = 0;
}

Menu::Menu(bool s) {
	state = s;
}

Menu::Menu(const Menu &other) {
	// TODO Auto-generated constructor stub
	state = other.state;
	profile = other.profile;
}

int Menu::getstat() const{
	return state;
}

void Menu::setstat(int s) {
	state = s;
}

void Menu::DisplayProfile() { //Function called when the player chooses the player profile option in the menu
	profile.ReadFromFile();
	DrawString( 200, 500, "Player Profile", colors[RED]);
	DrawString(30, 400, "Name: " + profile.getname(), colors[MINT_CREAM]);
	DrawString(30, 350, "Highscores: " + Num2Str(*(profile.gethighscores())), colors[MINT_CREAM]);
	DrawString(154, 325, Num2Str(*(profile.gethighscores() + 1)), colors[MINT_CREAM]);
	DrawString(154, 300, Num2Str(*(profile.gethighscores() + 2)), colors[MINT_CREAM]);
	DrawString(154, 275, Num2Str(*(profile.gethighscores() + 3)), colors[MINT_CREAM]);
}

void Menu::DisplayRules() { // Function called to display the rules when the player chooses the rules option in the menu
	DrawString( 200, 500, "HELP MENU", colors[RED]);
	DrawString( 10, 400, "Use the mouse to change the Position of the Gems.", colors[MISTY_ROSE]);
	DrawString( 10, 300, "Match the same Colour/Shape Gems with each other!!", colors[MISTY_ROSE]);
	DrawString( 10, 200, "If you get the required score in the given number of", colors[MISTY_ROSE]);
	DrawString( 10, 180, "moves, you win the level!", colors[MISTY_ROSE]);
}

void Menu::DrawMenu() { //  Function called at start of game to display the menu
	DrawString( 100, 500, "Press option number to choose it.", colors[RED]);
	DrawString( 200, 400, "1) Start New Game", colors[MISTY_ROSE]);
	DrawString( 200, 300, "2) See Player Profile", colors[MISTY_ROSE]);
	DrawString( 200, 200, "3) Game Rules", colors[MISTY_ROSE]);
	DrawString( 200, 100, "4) Exit", colors[MISTY_ROSE]);
}

void Menu::LostMenu() { // Function called to display the menu if the player loses the game
	DrawString(200, 400, "You lost the game ", colors[TURQUOISE]);
	DrawString(200, 350, "Your score was " + Num2Str(profile.getscore()), colors[TURQUOISE]);
	DrawString(200, 300, "Your level was " + Num2Str(profile.getlevel()), colors[TURQUOISE]);
}

void Menu::WonMenu() { // Function called to display the menu if the player wins the game
	DrawString(200, 400, "Congratulations!!!", colors[SEA_GREEN]);
	DrawString(200, 350, "You won the game!!", colors[SEA_GREEN]);
}

void Menu::PauseMenu() { // Function called to display the menu if the player pauses mid game
	DrawString( 100, 500, "Press option number to choose it.", colors[RED]);
	DrawString( 200, 400, "1) Resume Game", colors[MISTY_ROSE]);
	DrawString( 200, 300, "2) See Player Profile", colors[MISTY_ROSE]);
	DrawString( 200, 200, "3) Game Rules", colors[MISTY_ROSE]);
	DrawString( 200, 100, "4) Exit", colors[MISTY_ROSE]);
}

