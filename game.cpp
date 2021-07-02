//============================================================================
// Name        : .cpp
// Author      : Sibt ul Hussain
// Version     :
// Copyright   : (c) Reserved
// Description : Basic 2D game of Centipede...
//============================================================================

#ifndef CENTIPEDE_CPP_
#define CENTIPEDE_CPP_
#include "util.h"
#include "Player.h"
#include "Gem.h"
#include "GameBoard.h"
#include "Menu.h"
#include <iostream>
#include <string>
#include <cmath> // for basic math functions such as cos, sin, sqrt
#include <fstream>
using namespace std;
GameBoard G; // Creating my Single Global Object


// seed the random numbers generator by current time (see the documentation of srand for further help)...

/* Function sets canvas size (drawing area) in pixels...
 *  that is what dimensions (x and y) your game will have
 *  Note that the bottom-left coordinate has value (0,0) and top-right coordinate has value (width-1,height-1)
 * */
void SetCanvasSize(int width, int height) {
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, 0, height, -1, 1); // set the screen size to given width and height.
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity();
}


/*
 * Main Canvas drawing function.
 * */

void GameDisplay()/**/{
	// set the background color using function glClearColor.
	// to change the background play with the red, green and blue values below.
	// Note that r, g and b values must be in the range [0,1] where 0 means dim rid and 1 means pure red and so on.

	glClearColor(0/*Red Component*/, 0,	//148.0/255/*Green Component*/,
			0.0/*Blue Component*/, 0 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour
	glClear (GL_COLOR_BUFFER_BIT); //Update the colors

	//Calling the necessary functions to display the selected components
	if(G.getstate() == true) { //Drawing the main gameboard when the game starts
		G.DrawBoard();
	}
	if (G.getstat() == 0){ // Calling the function to draw the menu at the start of the game
		G.setstate(false);
		if(G.profile.getname().length() < 3) { // Taking input of name of player
			string s;
			cout << "Enter your name: ";
			getline(cin, s);
			G.profile.setname(s);
		}
		G.DrawMenu();
		glutPostRedisplay();
	}
	else if(G.getstat() == 2){ // Calling the function to display the profile if that option is chosen
		G.setstate(false);
		G.DisplayProfile();
		glutPostRedisplay();
	}
	else if(G.getstat() == 1) {
		G.setstate(true);
		glutPostRedisplay();
	}
	else if(G.getstat() == 3) { // Calling the function to display the rules if that option is chosen
		G.setstate(false);
		G.DisplayRules();
		glutPostRedisplay();
	}
	else if (G.getstat() == 4){ // Calling the function to display the pause menu if that option is chosen
		G.setstate(false);
		G.PauseMenu();
		glutPostRedisplay();
	}
	else if (G.getstat() == 5) { // Calling the function to display the lost menu if the conditions are fulfilled
		G.setstate(false);
		G.LostMenu();
		glutPostRedisplay();
	}
	else if (G.getstat() == 6) { // Calling the function to display the won menu if the conditions are fulfilled
		G.setstate(false);
		G.WonMenu();
		glutPostRedisplay();
	}

//	DrawCircle(50,670,10,colors[RED]);
//	DrawCircle(70,670,10,colors[RED]);
//	DrawCircle(90,670,10,colors[RED]);
//	DrawRoundRect(500,200,50,100,colors[DARK_SEA_GREEN],70);
//	DrawRoundRect(100,200,100,50,colors[DARK_OLIVE_GREEN],20);
//	DrawRoundRect(100,100,50,100,colors[DARK_OLIVE_GREEN],30);
//	DrawRoundRect(200,100,100,50,colors[LIME_GREEN],40);
//	DrawRoundRect(350,100,100,50,colors[LIME_GREEN],20);
//	Torus2d(100,500,50,50,50,50,3,colors[LIME_GREEN]);
	
	glutSwapBuffers(); // do not modify this line..

}

/*This function is called (automatically) whenever any non-printable key (such as up-arrow, down-arraw)
 * is pressed from the keyboard
 *
 * You will have to add the necessary code here when the arrow keys are pressed or any other key is pressed...
 *
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 *
 * */

void NonPrintableKeys(int key, int x, int y) {
	if (key
			== GLUT_KEY_LEFT /*GLUT_KEY_LEFT is constant and contains ASCII for left arrow key*/) {
		// what to do when left key is pressed...

	} else if (key
			== GLUT_KEY_RIGHT /*GLUT_KEY_RIGHT is constant and contains ASCII for right arrow key*/) {

	} else if (key
			== GLUT_KEY_UP/*GLUT_KEY_UP is constant and contains ASCII for up arrow key*/) {

	}

	else if (key
			== GLUT_KEY_DOWN/*GLUT_KEY_DOWN is constant and contains ASCII for down arrow key*/) {

	}

	/* This function calls the Display function to redo the drawing. Whenever you need to redraw just call
	 * this function*/

	glutPostRedisplay();

}

/*This function is called (automatically) whenever any printable key (such as x,b, enter, etc.)
 * is pressed from the keyboard
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 * */
void PrintableKeys(unsigned char key, int x, int y) {
	if (key == 27 || key == '4'/* Escape key ASCII*/) {
		G.profile.set(G.getscore(), G.getmoves(), G.getlevel());
		G.profile.WritetoFile();
		exit(1); // exit the program when escape key is pressed.
	}
	//Adding the options for the menu choices and the pause button
	if (key == '3') {
		G.setstat(3);
	}
	else if (key == '2') {
		G.setstat(2);
	}
	else if (key == 8) {
		G.setstat(0);
	}
	else if (key == '1') {
		G.setstat(1);
	}
	else if (key == 'P' or key == 'p') { // To pause mid game
		G.setstat(4);
	}
	else if (key == 'H' or key == 'h') {
		G.GiveHint();
	}
	glutPostRedisplay();
}

/*
 * This function is called after every 1000.0/FPS milliseconds
 * (FPS is defined on in the beginning).
 * You can use this function to animate objects and control the
 * speed of different moving objects by varying the constant FPS.
 *
 * */
void Timer(int m) {

	// implement your functionality here

	G.updatelevel();//Checking if a level has been passed
	if(G.getscore() == 0 and G.gettime() != 1) { // Functionality to make sure that level and score start at 0
			G.setscore(0);
			G.setlevel(1);
	}
	if(G.isLost() == true) { // Checking if Game has been lost
		G.setstat(5);
	}
	else if (G.isWon() == true) { // Checking if Game has been won
		G.setstat(6);
	}
	// once again we tell the library to call our Timer function after next 1000/FPS
	glutTimerFunc(100.0, Timer, 0);
}

/*This function is called (automatically) whenever your mouse moves witin inside the game window
 *
 * You will have to add the necessary code here for finding the direction of shooting
 *
 * This function has two arguments: x & y that tells the coordinate of current position of move mouse
 *
 * */
void MousePressedAndMoved(int x, int y) {
	//cout << x << " " << y << endl;
	//glutPostRedisplay();
}
void MouseMoved(int x, int y) {

	//glutPostRedisplay();
}

/*This function is called (automatically) whenever your mouse button is clicked witin inside the game window
 *
 * You will have to add the necessary code here for shooting, etc.
 *
 * This function has four arguments: button (Left, Middle or Right), state (button is pressed or released),
 * x & y that tells the coordinate of current position of move mouse
 *
 * */
void MouseClicked(int button, int state, int x, int y) {

	if (button == GLUT_LEFT_BUTTON) // dealing only with left button
			{

	} else if (button == GLUT_RIGHT_BUTTON) // dealing with right button
			{
			cout<<"Right Button Pressed"<<endl;
	}
	//Adding code for the swapping and moving of gems
	if( state == GLUT_DOWN and button == GLUT_LEFT_BUTTON) { // Called when a selected
		G.x1 = x;
		G.y1 = 600 - y;
	}
	if ( state == GLUT_UP and button == GLUT_LEFT_BUTTON) { // Called when the gem to be swapped is selected
		if (((G.x1 - x <= 120 and G.x1 - x >= 0) or (x - G.x1 >= 0 and x - G.x1 <= 120)) and (((G.y1 - (600 - y) <= 120 and G.y1 - (600 - y) >= 0)) or ((600 - y) - G.y1 >= 0 and (600 - y) - G.y1 <= 120))){
			G.updatetime(1);
			G.SwapGems(G.x1, G.y1, x, 600 - y); // Swap the gems if they are the clicked
			G.isMatch(x, 600 - y); // Checks immediately if the swapped gems match or not
			G.DropGems(); // Drops and adds new gems if gems did match
		}
	}
	glutPostRedisplay();
}
/*
 * our gateway main function
 * */
int main(int argc, char*argv[]) {

	int width = 600, height = 600; // i have set my window size to be 600 x 600

	InitRandomizer(); // seed the random number generator...
	glutInit(&argc, argv); // initialize the graphics library...
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // we will be using color display mode
	glutInitWindowPosition(50, 50); // set the initial position of our window
	glutInitWindowSize(width, height); // set the size of our window
	glutCreateWindow("Oonga Boonga"); // set the title of our game window
	SetCanvasSize(width, height); // set the number of pixels...

	// Register your functions to the library,
	// you are telling the library names of function to call for different tasks.
	//glutDisplayFunc(display); // tell library which function to call for drawing Canvas.

	glutDisplayFunc(GameDisplay); // tell library which function to call for drawing Canvas.
	glutSpecialFunc(NonPrintableKeys); // tell library which function to call for non-printable ASCII characters
	glutKeyboardFunc(PrintableKeys); // tell library which function to call for printable ASCII characters
	// This function tells the library to call our Timer function after 1000.0/FPS milliseconds...
	glutTimerFunc(100.0, Timer, 0);

	glutMouseFunc(MouseClicked);
	glutPassiveMotionFunc(MouseMoved); // Mouse
	glutMotionFunc(MousePressedAndMoved); // Mouse

	// now handle the control to library and it will call our registered functions when
	// it deems necessary...
	glutMainLoop();
	return 1;
}
#endif /* AsteroidS_CPP_ */
