#pragma once
#include<vector>
#include "SudokuGame.h"
#include<string>


#define SIZE 9
using namespace sf;
enum class EngineState {GAME, GAMEOVER};


class Input {
public:
	int intValue;
	std::string stringValue;
	Text cell;
	Input();
};

class SudokuEngine {
	int** sudokuLogic;
	int** sudokuView;
	bool** sudokuPlayer;
	std::vector<int> vector{ 1,2,3,4,5,6,7,8,9 };
	int positionCursor;
	Font font;
	EngineState engineState;
	int cellSize, fontSize;
	Input input;
public:
	SudokuEngine();
	void transposing();
	void swapColumn();
	void swapRow();
	void gameRandom();
	void flipGorizontaly();
	void flipVerticaly();
	bool CheckStep();
	bool runEngine(RenderWindow& _window, int level);
	void drawSquare(RenderWindow& window);
	void selectCell();
	bool checkRow(int row, int value);
	bool checkColumn(int col, int value);
	bool checkSquare(int row, int col, int value);
};

