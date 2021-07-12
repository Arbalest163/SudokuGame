#pragma once
#include<vector>
#include "SudokuGame.h"
#include<string>
#define SIZE 9 // ������ ����
using namespace sf;

enum class EngineState {GAME, GAMEOVER, WIN}; // ������� ����

class SudokuEngine {
private:
	int** sudokuLogic; // ���������� ����
	int** sudokuView; // ������������ ����
	bool** sudokuPlayer; // ���� �� ������ ������������� ���� ��� ������� ����� ����
	int** numberCursorMouse; // ��� ��������� ������� ����
	std::vector<int> vector{ 1,2,3,4,5,6,7,8,9 }; // �� �������� ����
	int positionCursor; // ������� ������� �� ����
	Vector2i posMouse; // ���������� ������� ����
	Font font; // �����
	EngineState engineState; // ������� ����
	int cellSize; // ������ ������ ����
	int fontSize; // ������ ������ ������ ����
	Texture backgroundTexture; // �������� ������� �����
	Sprite background; //  ������ ��� ������� ������� �����
public:
	SudokuEngine(); // ����������� ����
	~SudokuEngine(); // ���������� ����
	bool CheckWin(); // �������� ������
	bool checkFull();// �������� ����������� ����
	void setDifficulty(int difficulty); // ��������� ��������� ����
	bool runEngine(RenderWindow& window, int difficulty); // ������ ������ ����
	void drawSquare(RenderWindow& window); // ��������� ����
	void selectCell(); // ����� ������ � ���� ����
	bool checkRow(int row, int value); // �������� ������
	bool checkColumn(int col, int value); // �������� �������
	bool checkSquare(int row, int col, int value); // �������� ��������
private:
	void transposing(); // ���������������� ����
	void swapColumn(); // ����� ������� � �������� ����� ������
	void swapRow(); // ����� ����� � �������� ����� ������
	void gameRandom(); // ������������� ����
	void flipGorizontaly(); // �������� �� �����������
	void flipVerticaly(); // ��������� �� ���������
};

