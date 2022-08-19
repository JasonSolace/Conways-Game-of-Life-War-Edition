#pragma once


#ifndef CELL_cpp
#define CELL_cpp
#include "Cell.h"

using namespace std;

int roundToGrid(float numToRound); //Friend function to keep everything in a neat grid for us

Cells::Cells() 
{
	x = 100;
	y = 100;
	isAlive = true;
}

Cells::Cells(int locX, int locY) //Location X and Location Y
{
	x = roundToGrid(locX); //We the cells to be generated a certain size to form a grid
	y = roundToGrid(locY);
	isAlive = true;
}

Coordinate::Coordinate(int locX, int locY)
{
	x = roundToGrid(locX); //Similar to Cells constructor
	y = roundToGrid(locY);
}

bool Coordinate::operator <(const Coordinate& coord) const { //Used for Hashmap!!
	if (x < coord.x) //We first examine the X field. If x is less than the compared x, then we can stop and say this object is less than the compared
		return true;
	else if (y < coord.y && x == coord.x) //Otherwise, if x is equal to x, then we should compare the Y field. If this proves to be less, than we know for sure:
		return true;		
	return false;					//coord < compared_coord
}


Cells::~Cells() //Deconstructor, same as death for cell
{
	isAlive = false;
}

void Cells::drawSquare(Color color) //Draw Cell object onto window
{
	if (isAlive) //We want to make sure cell is alive
		DrawRectangle(x, y, width, height, color);
}

float Cells::getHeight() { //Getter functions since variables are private
	return height;
}
float Cells::getWidth() {
	return width;
}

void Cells::changeHeight(int locY) { //Setter Functions
	y = locY;
}
void Cells::changeWidth(int locX) {
	x = locX;
}
#endif