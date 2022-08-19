#include "Menu.h"
#include "raylib.h"
#include <iostream>

int roundToGrid(float numToRound)
{
	int check = floor(numToRound);
	int results = (( (check) / TESTGRID) * TESTGRID);
	return results;
}

void Menu::simulateLife(const map<Coordinate, Cells>& board, const map<Coordinate, Cells>& enemyBoard, map<Coordinate, Cells>& temp, const Coordinate coords)
{
	int results = 0;
	int x, y;
	for (int l = -TESTGRID; l <= TESTGRID; l = l + TESTGRID)
	{
		for (int k = -TESTGRID; k <= TESTGRID; k = k + TESTGRID)
		{
			x = coords.x + l;
			y = coords.y + k;
			for (int i = -TESTGRID; i <= TESTGRID; i = i + TESTGRID) //Examines x coord
			{
				for (int j = -TESTGRID; j <= TESTGRID; j = j + TESTGRID) //Examines y coord
				{

					if ( (board.count(Coordinate(x + i, y + j)) == 1 && !(x + i == x && y + j == y)) && (!enemyBoard.count(Coordinate(x + i, y + j)) == 1) ) { //If this "dead" cell has neighbors, record that in results. - Enemy cells do not count and are not considered friendly neighbors.
						results++;
					}
					//cout << "neighbors: " << results << "\toffset x: " << x << "\toffset y: " << y << "\tTx: " << x + i << "\tTy: " << y + j << "\tOfs: " << k << endl;
				}
			}
			if (results == 3)
				temp.insert(pair<Coordinate, Cells>(Coordinate(x, y), Cells(x, y)));
			results = 0;
		}
	}
	//cout << "End of Simulate Life function" << endl;
}


void Menu::simulateDeath(const map<Coordinate, Cells>& board, const map<Coordinate, Cells>& enemyBoard, map<Coordinate, Cells>& temp, const Coordinate coords)
{
	int results = 0, enemyResults = 0;
	for (int i = -TESTGRID; i <= TESTGRID; i = i + TESTGRID)
	{
		for (int j = -TESTGRID; j <= TESTGRID; j = j + TESTGRID) { //Essentially searching around each square to find its neighbors.
			if (board.count(Coordinate(coords.x + i, coords.y + j)) == 1 && !(coords.x + i == coords.x && coords.y + j == coords.y)) {
				results++;
			}

			if (enemyBoard.count(Coordinate(coords.x + i, coords.y + j)) == 1 && !(coords.x + i == coords.x && coords.y + j == coords.y)) {
				enemyResults++;
			}

		}
	}

	if (results < 2 || results > 3 || (enemyResults > results))
		temp.insert(pair<Coordinate, Cells>(Coordinate(coords.x, coords.y), Cells(coords.x, coords.y)));
}

//Important Functions Declarations. 
void Menu::SetUp() {
	bool isThereSquare = (!black.count(Coordinate(roundToGrid(GetMouseX()), roundToGrid(GetMouseY()))) && (GetMouseX() < GetScreenWidth()) && (GetMouseX() > 0)) && (!red.count(Coordinate(roundToGrid(GetMouseX()), roundToGrid(GetMouseY()))) && (GetMouseX() < GetScreenWidth()) && (GetMouseX() > 0));

	if (IsMouseButtonDown(0)) {
		//If we DONT find square in the grid(self or enemy), add it to the board hashmap
		if (isThereSquare) {
			black.insert(pair<Coordinate, Cells>(Coordinate(roundToGrid(GetMouseX()), roundToGrid(GetMouseY())), Cells(roundToGrid(GetMouseX()), roundToGrid(GetMouseY())))); //Add to hashmap
		}
	}

	if (IsMouseButtonDown(1)) {
		if (isThereSquare) //For Enemy Cell - Right click instead
			red.insert(pair<Coordinate, Cells>(Coordinate(roundToGrid(GetMouseX()), roundToGrid(GetMouseY())), Cells(roundToGrid(GetMouseX()), roundToGrid(GetMouseY()))));
	}

	if (IsMouseButtonDown(2)) {
		red.erase(Coordinate(roundToGrid(GetMouseX()), roundToGrid(GetMouseY())));
		black.erase(Coordinate(roundToGrid(GetMouseX()), roundToGrid(GetMouseY())));
	}
	//cout << "Black Size: " << black.size() << endl << "Red Size: " << red.size() << endl;
}

void Menu::ChangeBoard(map<Coordinate, Cells> &black, map<Coordinate, Cells>& red)
{
	map<Coordinate, Cells>::iterator it;
	map<Coordinate, Cells> tempLife, tempDeath;
	map<Coordinate, Cells> redTempLife, redTempDeath;

	//Began with Black's temp maps
	for (it = black.begin(); it != black.end(); it++) {
		simulateLife(black, red, tempLife, it->first);
	}

	for (it = black.begin(); it != black.end(); it++) {
		simulateDeath(black, red, tempDeath, it->first);
	}

	
	//Began with Red's temp maps
	for (it = red.begin(); it != red.end(); it++) {
		simulateLife(red, black, redTempLife, it->first);
	}

	for (it = red.begin(); it != red.end(); it++) {
		simulateDeath(red, black, redTempDeath, it->first);
	}

	//Began Copying over black's map
	for (it = tempLife.begin(); it != tempLife.end(); it++)
	{
		black.insert(pair<Coordinate, Cells>(it->first, it->second));
	}

	for (it = tempDeath.begin(); it != tempDeath.end(); it++)
	{
		black.erase(it->first);
	}

	//Began Coping over red's map
	for (it = redTempLife.begin(); it != redTempLife.end(); it++)
	{
		red.insert(pair<Coordinate, Cells>(it->first, it->second));
	}

	for (it = redTempDeath.begin(); it != redTempDeath.end(); it++)
	{
		red.erase(it->first);
	}

	//Clear temp variables
	tempDeath.clear();
	tempLife.clear();
	redTempDeath.clear();
	redTempLife.clear();
}

void Menu::DrawAllSquares()
{
	map<Coordinate, Cells>::iterator it;
	for (it = black.begin(); it != black.end(); ++it) { //Began to go through each square that exists in board, and:
		it->second.drawSquare(BLACK);				//Draw the square in its respected location
	}
	for (it = red.begin(); it != red.end(); ++it) { //Began to go through each square that exists in board, and:
		it->second.drawSquare(RED);				//Draw the square in its respected location
	}
}

void Menu::SpaceBarTriggerGame() 
{
	if (IsKeyPressed(KEY_SPACE)) { //Go between simulation and setup
		gameReady = !gameReady;
		controlVSYNC = 0;
	}
}

void Menu::RunSimulation()
{
	SpaceBarTriggerGame();
	//Start Simulation - meaning not paused
	if (gameReady)
	{
		DrawText("Running", GetScreenWidth() / 2 - 35, 20, 35, BLUE);
		if (controlVSYNC < 1) {
			SetTargetFPS(10);
			controlVSYNC++;
		}

		ChangeBoard(black, red);
	}
	else {
		DrawText("Paused", GetScreenWidth() / 2 - 35, 20, 35, PURPLE);
		if (controlVSYNC < 1) {
			SetTargetFPS(FLAG_VSYNC_HINT);
			controlVSYNC++;
		}
	}
}

int Menu::getRedSize() {
	return red.size();
}

int Menu::getBlackSize() {
	return black.size();
}

Menu::Menu()
{
	isInMenu = true;
	gameReady = false;
}

bool Menu::GetMenu() 
{
	return isInMenu;
}

void Menu::ChangeMenu() 
{
	if (IsMouseButtonReleased(0)){
		isInMenu = false;
	}
}

/*Old Functions that are removed:
* 
* 
void Menu::DrawSettings() //No longer needed. Originally was going to give the option to change the frame rate, but I decided against it.
{
	char showSpeed[20];
	strcpy_s(showSpeed, to_string(speed).c_str());

	DrawLine(100, 100, 200, 100, WHITE);
	DrawLine(100, 100, 100, 200, WHITE);
	DrawLine(200, 100, 200, 200, WHITE);
	DrawLine(100, 150, 200, 150, WHITE);
	DrawLine(100, 200, 200, 200, WHITE);
	DrawText("Increase FPS", 110, 125, 10, YELLOW);
	DrawText("Decrease FPS", 110, 160, 10, YELLOW);

	if (!gameReady)
		DrawText("Paused", GetScreenWidth() / 2, 50, 20, YELLOW);
	else
		DrawText("Running", GetScreenWidth() / 2, 50, 20, YELLOW);
	
	if (GetMouseX() > 100 && GetMouseX() < 200 && GetMouseY() > 100 && GetMouseY() < 150 && IsMouseButtonPressed(0))
		speed += 2;
	if (GetMouseX() > 100 && GetMouseX() < 200 && GetMouseY() > 150 && GetMouseY() < 200 && IsMouseButtonPressed(0) && speed > 0)
		speed -= 2;
}

void Menu::RunMenu()  //Player used to be able to go back between menu and simulation. It worked, but there is really no point to go back to the menu.
{
	if (isInMenu) {
		DrawSettings();
		ClearBackground(BLACK); // Set background color (framebuffer clear color)
		int menuTextWidth = MeasureText("Conways Game of Life", 70);
		DrawText("Conways Game of Life", GetScreenWidth() / 2 - menuTextWidth / 2, GetScreenHeight() / 3, 70, WHITE);
		menuTextWidth = MeasureText("Q to Enter/Leave Menu\nSpaceBar to Run/Pause Simulation", 60);
		DrawText("Q to Enter/Leave Menu\nSpaceBar to Run/Pause Simulation", GetScreenWidth() / 2 - menuTextWidth / 2, GetScreenHeight() / 1.7, 60, WHITE);
	}
}
 */
