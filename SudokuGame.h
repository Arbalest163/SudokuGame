#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include<time.h>
#include<Windows.h>
#include "SudookuEngine.h"


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



