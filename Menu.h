#pragma once
#ifndef MENU_H
#define MENU_H

#include "raylib.h"
#include "Cell.h"
#include <string>
#include <stdio.h>
#include <math.h>
#include <iostream>

class Menu 
{
private:
	bool isInMenu; //Checks if we're in the menu or not
	bool gameReady; //This starts / stops simulation on the go
	map<Coordinate, Cells> black; //Board the cells will be stored in - Hashmap
	map<Coordinate, Cells> red;
	int controlVSYNC = 0;
	int blackSize;
	int redSize;
public:
	Menu(); //Constructor 
	bool GetMenu();
	void ChangeMenu();
	void SpaceBarTriggerGame();
	void RunSimulation();
	void SetUp();
	void ChangeBoard(map<Coordinate, Cells>& board, map<Coordinate, Cells>& enemyBoard);
	void DrawAllSquares();
	void simulateDeath(const map<Coordinate, Cells>& board, const map<Coordinate, Cells>& enemyBoard, map<Coordinate, Cells>& temp, const Coordinate coords);
	void simulateLife(const map<Coordinate, Cells>& board, const map<Coordinate, Cells>& enemyBoard, map<Coordinate, Cells>& temp, const Coordinate coords);
	friend int roundToGrid(float numToRound);
	int getRedSize();
	int getBlackSize();

	/*Function Declarations that were removed:
	 	void RunMenu();
	 	void DrawSettings();
	*/
};

#endif