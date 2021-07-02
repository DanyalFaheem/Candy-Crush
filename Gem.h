/*
 * Gem.h
 *
 *  Created on: May 9, 2020
 *      Author: danyal-faheem
 */

#ifndef GEM_H_
#define GEM_H_
#include <iostream>
#include <string>
using namespace std;

class Gem {
private:
	string type;
public:
	double x, y;
	Gem();
	Gem(string);
	Gem(const Gem &other);
	string gettype() const;
	void settype(string);
	void DrawGem(double,double);
	void DrawHint();
};

#endif /* GEM_H_ */
