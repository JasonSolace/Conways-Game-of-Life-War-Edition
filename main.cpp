/*
Created by: Jason Armenta
Conways Game of Life with Raylib
*/
#include "Cell.h"
#include "Menu.h"

int main() {
	SetConfigFlags(FLAG_WINDOW_RESIZABLE); //We allow the user to resize. --Can maybe cause some bugs
	InitWindow(1450, 700, "Game of Life"); //Window size, title of program
	SetWindowMinSize(1450, 700);
	SetTargetFPS(FLAG_VSYNC_HINT); //VSYNC of individuals monitor
	Menu menu; //Although called menu, this class ontop of handling menu also controls gamestates and board changes through the game
	bool rulesPrompt = true;
	float splashTimer = 0.0;
	const char* conwaysRules = "Conways Game of Life Rules\n1. Any live cell with fewer than two live nieghbors dies, as if by underpopulation\n"
		"2. Any live cell with two or three live neighbors lives on to the next generation.\n"
		"3. Any live cell with more than three live neighbors dies, as if by overpopulation";
	const char* warRules = "War Edition Rules\n1. Any live cell with any enemy neighbors will not reproduce\n"
		"2. If there are more enemy neighbors than allies, cell will automatically die";
	const char* controls = "Controls\nLeft Click to spawn black cell.\nRight Click to spawn red cell\nMiddle click to delete\nSpacebar to run or pause simulation";
	const char* clickToContinue = "CLICK ANYWHERE TO CONTINUE";
	int introTextWidth = MeasureText(clickToContinue, 50);
	char blackScore[5], redScore[5];

	Texture2D logo = LoadTexture("resources/attempt.png");
	Texture2D title = LoadTexture("resources/title.png");
	Font font = LoadFontEx("resources/Silkscreen.ttf", 64, 0, NULL);

	while (!WindowShouldClose())
	{
		if (splashTimer > 100)
		{
			menu.ChangeMenu(); //Has a "one time use" where menu is over.
			if (!rulesPrompt) {
				menu.SetUp();
				menu.RunSimulation(); //This runs the simulation, essentially the logic portion of the simulation
			}

			BeginDrawing();
			if (rulesPrompt) {
				if (menu.GetMenu()) {
					ClearBackground(ColorFromNormalized({ 1.0, 0.52, 0.54, 1.0 }));
					DrawTexture(title, GetScreenWidth() / 2 - (1200 / 2), GetScreenHeight() / 2 - (900 / 2), WHITE);
					DrawTextEx(font, clickToContinue, Vector2{ (float)GetScreenWidth() / 2 - (introTextWidth / 2), (float)GetScreenHeight() - 100 }, 50, 0, BLACK);
				}
				else {
					ClearBackground(ColorFromNormalized({ 1.0, 0.52, 0.54, 1.0 }));
					DrawTextEx(font, conwaysRules, Vector2{ 35 , 100 }, 32, 0, BLACK);
					DrawTextEx(font, warRules, Vector2{ 35 , 300 }, 32, 0, BLACK);
					DrawTextEx(font, controls, Vector2{ (float)GetScreenWidth() / 2 - MeasureText(controls, 50) / 2, (float)GetScreenHeight() / 2 + 150 }, 32, 0, BLACK);
					DrawTextEx(font, clickToContinue, Vector2{ (float)GetScreenWidth() / 2 + introTextWidth / 2 - 200, (float)GetScreenHeight() - 100 }, 35, 0, BLACK);
					if (IsMouseButtonPressed(0))
						rulesPrompt = false;
				}
			}
			if (!rulesPrompt) {
				ClearBackground(WHITE);
				strcpy_s(blackScore, to_string(menu.getBlackSize()).c_str());
				strcpy_s(redScore, to_string(menu.getRedSize()).c_str());
				menu.DrawAllSquares();
				DrawText(blackScore, 30, 30, 50, BLACK);
				DrawText(redScore, GetScreenWidth() - 110, 30, 50, RED);

			}

			EndDrawing(); //End of drawing
		} //Runs JasonSolace intro for a bit then moves on. Might need to make this better - different vsyncs can cause this to be an issue!
		else
		{
			BeginDrawing();
			ClearBackground(BLACK);
			DrawTexture(logo, GetScreenWidth() / 2 - 250, GetScreenHeight() / 2 - 200, WHITE);
			EndDrawing();
			splashTimer += 1;
		}
	}

	CloseWindow();
	return 0;
}


