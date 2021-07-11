#include "SudookuEngine.h"

SudokuEngine::SudokuEngine()
	: positionCursor{ 0 }, cellSize{ 90 }, fontSize{ 45 }, posMouse{0,0}
{
	engineState = EngineState::GAME;
	font.loadFromFile("Black-Acute.ttf");
	sudokuLogic = new int* [SIZE];
	sudokuView = new int* [SIZE];
	sudokuPlayer = new bool* [SIZE];
	numberCursorMouse = new int* [SIZE];
	for (int i{ 0 }; i < SIZE; i++) {
		if (i == 0) {
			sudokuLogic[i] = new int[SIZE * SIZE]{0};
			sudokuView[i] = new int[SIZE * SIZE]{0};
			sudokuPlayer[i] = new bool[SIZE * SIZE]{0};
			numberCursorMouse[i] = new int[SIZE * SIZE]{0};
		}
		else {
			sudokuLogic[i] = sudokuLogic[i - 1] + SIZE;
			sudokuView[i] = sudokuView[i - 1] + SIZE;
			sudokuPlayer[i] = sudokuPlayer[i - 1] + SIZE;
			numberCursorMouse[i] = numberCursorMouse[i - 1] + SIZE;
		}
	}
	for (int i{ 0 },k{0}; i < SIZE; ++i) {
		if (i == 1) rotate(vector.begin(), vector.begin() + 3, vector.end());
		if (i == 2) rotate(vector.begin(), vector.begin() + 3, vector.end());
		if (i == 3) rotate(vector.begin(), vector.begin() + 4, vector.end());
		if (i == 4) rotate(vector.begin(), vector.begin() + 3, vector.end());
		if (i == 5) rotate(vector.begin(), vector.begin() + 3, vector.end());
		if (i == 6) rotate(vector.begin(), vector.begin() + 4, vector.end());
		if (i == 7) rotate(vector.begin(), vector.begin() + 3, vector.end());
		if (i == 8) rotate(vector.begin(), vector.begin() + 3, vector.end());
		for (int j{ 0 }, v{ 0 }; j < SIZE; j++, v++, k++) {
			sudokuLogic[i][j] = vector[v];
			sudokuView[i][j] = vector[v];
			sudokuPlayer[i][j] = true;
			numberCursorMouse[i][j] = k;
		}
	}
}
void SudokuEngine::transposing() {
	SudokuEngine tmp;
	for (int i{ 0 }; i < SIZE; ++i) {
		for (int j{ 0 }; j < SIZE; j++) {
			sudokuLogic[i][j] = tmp.sudokuLogic[j][i];
		}
	}
}
void SudokuEngine::swapColumn() {
	int x = rand() % 9;
	int y{ 0 };
	x == 0 || x == 3 || x == 6 ? y = x + (rand() % 2 + 1) : y = x - 1;
	for (int i{ 0 }; i < 9; ++i) {
		std::swap(sudokuLogic[i][x], sudokuLogic[i][y]);
	}
}
void SudokuEngine::swapRow() {
	int x = rand() % 9;
	int y{ 0 };
	x == 0 || x == 3 || x == 6 ? y = x + 1 : y = x - 1;
	for (int i{ 0 }; i < SIZE; ++i) {
		std::swap(sudokuLogic[x][i], sudokuLogic[y][i]);
	}
}
void SudokuEngine::flipGorizontaly() {

	for (int i{ 0 }, k{ SIZE - 1 }; i < SIZE / 2; ++i, k--) {
		for (int j{ 0 }; j < SIZE; j++) {
			std::swap(sudokuLogic[i][j], sudokuLogic[k][j]);
		}
	}
}
void SudokuEngine::flipVerticaly() {

	for (int i{ 0 }; i < SIZE; ++i) {
		for (int j{ 0 }, k{ SIZE - 1 }; j < SIZE / 2; j++, k--) {
			std::swap(sudokuLogic[i][j], sudokuLogic[i][k]);
		}
	}
}
void SudokuEngine::gameRandom() {
	for (int random_value{ rand() % 100 }; random_value > 0; random_value--) {
		transposing();
		flipGorizontaly();
		flipVerticaly();
		swapColumn();
		swapRow();
	}
}

bool SudokuEngine::CheckStep() {
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			if (sudokuView[i][j] == 0) {
				return true;
			}
		}
	}
	return false;
}
void SudokuEngine::setDifficulty(int difficulty)
{
	int amount{2};
	switch (difficulty)
	{
	case 0:
		amount = 2;
		break;
	case 1:
		amount = 3;
		break;
	case 2:
		amount = 5;
		break;
	default:
		amount = 2;
		break;
	}
	int numberCells = SIZE * SIZE;
	int deleted = numberCells - numberCells / amount;
	int row = rand() % SIZE;
	int column = rand() % SIZE;
	for (int i = 0; i < deleted; i++)
	{
		if (sudokuView[row][column] > 0)
		{
			sudokuView[row][column] = 0;
			sudokuPlayer[row][column] = false;
		}
		else
		{
			row = rand() % SIZE;
			column = rand() % SIZE;
			i--;
		}
	}
}

bool SudokuEngine::checkRow(int row, int value) {

	for (int i = 0; i < SIZE; i++)
	{
		if (sudokuView[row][i] == value)
		{
			return false;
		}
	}
	return true;
}
bool SudokuEngine::checkColumn(int col, int value) {

	for (int i = 0; i < SIZE; i++)
	{
		if (sudokuView[col][i] == value)
		{
			return false;
		}
	}
	return true;
}
bool SudokuEngine::checkSquare(int row, int col, int value) {
	int quadx = 3, quady = 3;
	int sizey = row / quady;
	int sizex = col / quadx;
	sizey *= quady;
	sizex *= quadx;
	for (int i = sizey; i < sizey + quady; i++)
	{
		for (int j = sizex; j < sizex + quadx; j++)
		{
			if (sudokuView[i][j] == value)
			{
				return false;
			}
		}
	}
	return true;
}

void SudokuEngine::drawSquare(RenderWindow& window)
{
	int quadx = 3, quady = 3;

	RectangleShape mediumSquare;
	mediumSquare.setSize(Vector2f(cellSize * quadx, cellSize * quady));
	mediumSquare.setOutlineThickness(5);
	mediumSquare.setOutlineColor(Color::Red);
	mediumSquare.setFillColor(Color::Transparent);

	RectangleShape bigSquare;
	bigSquare.setSize(Vector2f(cellSize * SIZE, cellSize * SIZE));
	bigSquare.setOutlineThickness(10);
	bigSquare.setOutlineColor(Color::Yellow);
	bigSquare.setFillColor(Color::Transparent);
	bigSquare.setPosition(cellSize, cellSize);

	RectangleShape smallSquare;
	smallSquare.setSize(Vector2f(cellSize, cellSize));
	smallSquare.setOutlineThickness(1);
	smallSquare.setOutlineColor(Color::White);
	smallSquare.setFillColor(Color::Transparent);

	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			std::string text;
			if (sudokuView[i][j] > 0)
			{
				text = std::to_string(sudokuView[i][j]);
			}
			else
			{
				text = "";
			}
			if (j == positionCursor % SIZE && i == positionCursor / SIZE)
			{
				smallSquare.setFillColor(Color(0, 255, 80, 210));
			}
			smallSquare.setPosition(cellSize + j * cellSize, cellSize + i * cellSize);
			window.draw(smallSquare);
			smallSquare.setFillColor(Color::Transparent);
			Text cellText(text, font, fontSize);
			cellText.setPosition(cellSize + j * cellSize + fontSize/2, cellSize + i * cellSize + fontSize/2);
			if (sudokuPlayer[i][j])
			{
				cellText.setFillColor(Color::Black);
			}
			else
			{
				cellText.setFillColor(Color::Blue);
			}


			window.draw(cellText);
		}
	}
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			if (i % quady == 0 && j % quadx == 0)
			{
				mediumSquare.setPosition(cellSize + j * cellSize, cellSize + i * cellSize);
				window.draw(mediumSquare);
			}
		}
	}
	window.draw(bigSquare);
}

bool SudokuEngine::runEngine(RenderWindow& window, int difficulty)
{
	Texture backgroundTexture;
	backgroundTexture.loadFromFile("Background.jpg");
	Sprite background(backgroundTexture);
	gameRandom();
	setDifficulty(difficulty);
	while (window.isOpen())
	{
		Event event;
		posMouse = Mouse::getPosition(window);
		//std::cout << posMouse.x / cellSize << "  " << posMouse.y / cellSize << std::endl;
		
		while (window.pollEvent(event) && engineState == EngineState::GAME)
		{
			if (event.type == Event::Closed) {
				delete[]sudokuLogic[0];
				delete[]sudokuView[0];
				delete[]sudokuPlayer[0];
				window.close();
			}

			if (event.type == Event::KeyPressed) {

				if ((Keyboard::isKeyPressed(Keyboard::Escape)))
				{
					delete[]sudokuLogic[0];
					delete[]sudokuView[0];
					delete[]sudokuPlayer[0];
					return false;
				}
				selectCell();
			}
			if (event.type == Event::MouseButtonPressed) {
				selectCell();
			}
		}
		window.clear();
		window.draw(background);
		drawSquare(window);
		
		window.display();
	}
	return true;
}

void SudokuEngine::selectCell()
{
	if (Keyboard::isKeyPressed(Keyboard::Left))
	{
		positionCursor--;
		if (positionCursor < 0)
		{
			positionCursor = SIZE * SIZE - 1;
		}
	}
	if (Keyboard::isKeyPressed(Keyboard::Right))
	{
		positionCursor++;
		if (positionCursor > SIZE * SIZE - 1)
		{
			positionCursor = 0;
		}
	}
	if (Keyboard::isKeyPressed(Keyboard::Up))
	{
		positionCursor -= SIZE;
		if (positionCursor < 0)
		{
			positionCursor = ((SIZE * SIZE)) - SIZE + ((positionCursor + SIZE) % SIZE);
		}
	}

	if (Keyboard::isKeyPressed(Keyboard::Down))
	{
		positionCursor += SIZE;
		if (positionCursor > SIZE * SIZE - 1)
		{
			positionCursor = positionCursor % SIZE;
		}
	}
	if (Mouse::isButtonPressed(Mouse::Left)) {
		
		if (posMouse.x > cellSize && posMouse.x < cellSize * SIZE + cellSize
			&& posMouse.y > cellSize && posMouse.y < cellSize * SIZE + cellSize) {
			int x = posMouse.x / cellSize;
			int y = posMouse.y / cellSize;
			positionCursor = numberCursorMouse[y - 1][x - 1];
		}
	}
	if (!sudokuPlayer[positionCursor / SIZE][positionCursor % SIZE])
	{
		if (Keyboard::isKeyPressed(Keyboard::Num0) || Keyboard::isKeyPressed(Keyboard::Numpad0))
		{
			sudokuView[positionCursor / SIZE][positionCursor % SIZE] = 0;
		}
		if (Keyboard::isKeyPressed(Keyboard::Num1) || Keyboard::isKeyPressed(Keyboard::Numpad1))
		{
			sudokuView[positionCursor / SIZE][positionCursor % SIZE] = 1;
		}
		if (Keyboard::isKeyPressed(Keyboard::Num2) || Keyboard::isKeyPressed(Keyboard::Numpad2))
		{
			sudokuView[positionCursor / SIZE][positionCursor % SIZE] = 2;
		}
		if (Keyboard::isKeyPressed(Keyboard::Num3) || Keyboard::isKeyPressed(Keyboard::Numpad3))
		{
			sudokuView[positionCursor / SIZE][positionCursor % SIZE] = 3;
		}
		if (Keyboard::isKeyPressed(Keyboard::Num4) || Keyboard::isKeyPressed(Keyboard::Numpad4))
		{
			sudokuView[positionCursor / SIZE][positionCursor % SIZE] = 4;
		}
		if (Keyboard::isKeyPressed(Keyboard::Num5) || Keyboard::isKeyPressed(Keyboard::Numpad5))
		{
				sudokuView[positionCursor / SIZE][positionCursor % SIZE] = 5;
		}
		if (Keyboard::isKeyPressed(Keyboard::Num6) || Keyboard::isKeyPressed(Keyboard::Numpad6))
		{
				sudokuView[positionCursor / SIZE][positionCursor % SIZE] = 6;
		}
		if (Keyboard::isKeyPressed(Keyboard::Num7) || Keyboard::isKeyPressed(Keyboard::Numpad7))
		{
				sudokuView[positionCursor / SIZE][positionCursor % SIZE] = 7;
		}
		if (Keyboard::isKeyPressed(Keyboard::Num8) || Keyboard::isKeyPressed(Keyboard::Numpad8))
		{
				sudokuView[positionCursor / SIZE][positionCursor % SIZE] = 8;
		}
		if (Keyboard::isKeyPressed(Keyboard::Num9) || Keyboard::isKeyPressed(Keyboard::Numpad9))
		{
			sudokuView[positionCursor / SIZE][positionCursor % SIZE] = 9;
		}
		if (Keyboard::isKeyPressed(Keyboard::BackSpace))
		{
			sudokuView[positionCursor / SIZE][positionCursor % SIZE] = 0;
		}
	}
}

