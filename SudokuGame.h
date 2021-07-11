#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include<time.h>
#include<Windows.h>
#include "SudookuEngine.h"
#define SIZE_H 1920
#define SIZE_V 1080

using namespace sf;

enum class GameState { MENU, GAME, END };

class SudokuGame
{
private: 
	Font font;
	GameState state;
	void levels();
	void menu();

public:
	SudokuGame();
	~SudokuGame();
	void runGame();


};



