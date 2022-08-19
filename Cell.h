#pragma once

#ifndef CELL_H
#define CELL_H
#include "raylib.h"
#include <map>
#include <string>

using namespace std;
const int TESTGRID = 10;


class Cells
{
public:
	Cells(); //Constructors
	Cells(int locX, int locY);
	~Cells(); //Deconstructor
	void drawSquare(Color color); //Draw cell onto screen
	float getHeight(); //Getter Function
	float getWidth(); //Getter Function
	void changeHeight(int locY);  //Setter Function
	void changeWidth(int locX);
private:
	float x, y; //Specifically used to draw the cell onto the screen for the user to see. These should match Coordinate's coords when being looked for.
	float width = TESTGRID, height = TESTGRID; //This is the SIZE of the cube! If we change the grid, the size of cube will change with it
	bool isAlive; //Used to determine if cube is alive. A little redudant, as a dead cell actually deletes the object
};

struct Coordinate //Object is used as a key for cells - it's only purpose is to help us locate the cells
{
	float x, y;
	Coordinate(int locX, int locY);
public:
	bool operator <(const Coordinate& coord) const; //Needed for hashmap! Objects need to be compared between eachother

};
#endif