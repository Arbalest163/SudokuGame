#include "SudookuEngine.h"


Input::Input() : intValue(0), stringValue("")
{
}

SudokuEngine::SudokuEngine()
	: positionCursor{ 0 }, cellSize{ 40 }, fontSize{20}
{
	engineState = EngineState::GAME;
	font.loadFromFile("Black-Acute.ttf");
	sudokuLogic = new int* [SIZE];
	sudokuView = new int* [SIZE];
	sudokuPlayer = new bool* [SIZE];
	for (int i{ 0 }; i < SIZE; i++) {
		if (i == 0) {
			sudokuLogic[i] = new int[SIZE*SIZE];
			sudokuView[i] = new int[SIZE*SIZE];
			sudokuPlayer[i] = new bool[SIZE*SIZE];
		}
		else {
			sudokuLogic[i] = sudokuLogic[i - 1] + SIZE;
			sudokuView[i] = sudokuView[i - 1] + SIZE;
			sudokuPlayer[i] = sudokuPlayer[i - 1] + SIZE;
		}
	}
	for (int i{ 0 }; i < SIZE; ++i) {
		if (i == 1) rotate(vector.begin(), vector.begin() + 3, vector.end());
		if (i == 2) rotate(vector.begin(), vector.begin() + 3, vector.end());
		if (i == 3) rotate(vector.begin(), vector.begin() + 4, vector.end());
		if (i == 4) rotate(vector.begin(), vector.begin() + 3, vector.end());
		if (i == 5) rotate(vector.begin(), vector.begin() + 3, vector.end());
		if (i == 6) rotate(vector.begin(), vector.begin() + 4, vector.end());
		if (i == 7) rotate(vector.begin(), vector.begin() + 3, vector.end());
		if (i == 8) rotate(vector.begin(), vector.begin() + 3, vector.end());
		for (int j{ 0 }, v{ 0 }; j < SIZE; j++, v++) {
			sudokuLogic[i][j] = vector[v];
			sudokuView[i][j] = 0;
			sudokuPlayer[i][j] = true;
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
	mediumSquare.setOutlineThickness(2);
	mediumSquare.setOutlineColor(sf::Color::Black);
	//quadradog.setOutlineColor(sf::Color::Red);
	mediumSquare.setFillColor(sf::Color::Transparent);

	RectangleShape bigSquare;
	bigSquare.setSize(Vector2f(cellSize * SIZE, cellSize * SIZE));
	bigSquare.setOutlineThickness(4);
	bigSquare.setOutlineColor(sf::Color::Black);
	//quadradofull.setOutlineColor(sf::Color::Red);
	bigSquare.setFillColor(sf::Color::Transparent);
	bigSquare.setPosition((400 - SIZE / 2 * cellSize), (300 - SIZE / 2 * cellSize));

	RectangleShape smallSquare;
	smallSquare.setSize(Vector2f(cellSize, cellSize));
	smallSquare.setOutlineThickness(1);
	smallSquare.setOutlineColor(Color(200, 200, 200));
	smallSquare.setFillColor(sf::Color::Transparent);

	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			smallSquare.setPosition((400 - SIZE / 2 * cellSize) + j * cellSize, (300 - SIZE / 2 * cellSize) + i * cellSize);
			window.draw(smallSquare);
			std::string text;
			if (sudokuLogic[i][j] > 0)
			{
				text = std::to_string(sudokuLogic[i][j]);
			}
			else
			{
				text = "";
			}
			if (positionCursor % SIZE == j && positionCursor / SIZE == i)
			{
				smallSquare.setFillColor(Color(0, 255, 0, 210));
				smallSquare.setPosition((400 - SIZE / 2 * cellSize) + j * cellSize, (300 - SIZE / 2 * cellSize) + i * cellSize);
				window.draw(smallSquare);
				smallSquare.setFillColor(sf::Color::Transparent);
			}

			Text cell(text, font, fontSize);
			cell.setPosition((400 - SIZE / 2 * cellSize) + j * cellSize + fontSize / 2, (300 - SIZE / 2 * cellSize) + i * cellSize + fontSize / 2);
			if (sudokuPlayer[i][j])
			{
				cell.setFillColor(Color(80, 80, 80));
			}
			else
			{
				cell.setFillColor(Color::Blue);
			}


			window.draw(cell);
		}
	}
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			if (i % quady == 0 && j % quadx == 0)
			{
				mediumSquare.setPosition((400 - SIZE / 2 * cellSize) + j * cellSize, (300 - SIZE / 2 * cellSize) + i * cellSize);
				window.draw(mediumSquare);
			}
		}
	}
	window.draw(bigSquare);
}

bool SudokuEngine::runEngine(RenderWindow& window, int level)
{
	gameRandom();
	while (window.isOpen())
	{
		Event event;
	

		while (window.pollEvent(event) && engineState == EngineState::GAME)
		{
			
			switch (event.type)
			{
			
			case Event::Closed:
				delete[]sudokuLogic[0];
				delete[]sudokuView[0];
				delete[]sudokuPlayer[0];
				window.close();
				break;

			case Event::KeyPressed:

				if ((Keyboard::isKeyPressed(Keyboard::Escape)))
				{
					delete[]sudokuLogic[0];
					delete[]sudokuView[0];
					delete[]sudokuPlayer[0];
					return false;
				}
				selectCell();
				break;

			default:
				break;
			}

		}
		

		window.clear();
		drawSquare(window);
		input.cell.setCharacterSize(20);
		input.cell.setFillColor(Color(255, 80, 80));
		input.cell.setFont(font);
		input.cell.setString(input.stringValue);
		input.cell.setPosition(10, 10);
		input.cell.setPosition((400 - SIZE / 2 * cellSize) + positionCursor % SIZE * cellSize + fontSize / 2, (300 - SIZE / 2 * cellSize) + positionCursor / SIZE * cellSize + fontSize / 2);

		window.draw(input.cell);

		
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
		input.stringValue = "";
	}

	if (Keyboard::isKeyPressed(Keyboard::Right))
	{
		positionCursor++;
		if (positionCursor > SIZE * SIZE - 1)
		{
			positionCursor = 0;
		}
		input.stringValue = "";
	}
	if (Keyboard::isKeyPressed(Keyboard::Up))
	{
		positionCursor -= SIZE;
		if (positionCursor < 0)
		{
			positionCursor = ((SIZE * SIZE)) - SIZE + ((positionCursor + SIZE) % SIZE);
		}
		input.stringValue = "";
	}

	if (Keyboard::isKeyPressed(Keyboard::Down))
	{
		positionCursor += SIZE;
		if (positionCursor > SIZE * SIZE - 1)
		{
			positionCursor = positionCursor % SIZE;
		}
		input.stringValue = "";
	}
	if (!sudokuPlayer[positionCursor / SIZE][positionCursor % SIZE] && input.stringValue.size() <= 1)
	{
		if (Keyboard::isKeyPressed(Keyboard::Num0) || Keyboard::isKeyPressed(Keyboard::Numpad0))
		{
			input.stringValue += '0';
		}
		if (Keyboard::isKeyPressed(Keyboard::Num1) || Keyboard::isKeyPressed(Keyboard::Numpad1))
		{
			input.stringValue += '1';
		}
		if (Keyboard::isKeyPressed(Keyboard::Num2) || Keyboard::isKeyPressed(Keyboard::Numpad2))
		{
			input.stringValue += '2';
		}
		if (Keyboard::isKeyPressed(Keyboard::Num3) || Keyboard::isKeyPressed(Keyboard::Numpad3))
		{
			input.stringValue += '3';
		}
		if (Keyboard::isKeyPressed(Keyboard::Num4) || Keyboard::isKeyPressed(Keyboard::Numpad4))
		{
			input.stringValue += '4';
		}
		if (Keyboard::isKeyPressed(Keyboard::Num5) || Keyboard::isKeyPressed(Keyboard::Numpad5))
		{
			input.stringValue += '5';
		}
		if (Keyboard::isKeyPressed(Keyboard::Num6) || Keyboard::isKeyPressed(Keyboard::Numpad6))
		{
			input.stringValue += '6';
		}
		if (Keyboard::isKeyPressed(Keyboard::Num7) || Keyboard::isKeyPressed(Keyboard::Numpad7))
		{
			input.stringValue += '7';
		}
		if (Keyboard::isKeyPressed(Keyboard::Num8) || Keyboard::isKeyPressed(Keyboard::Numpad8))
		{
			input.stringValue += '8';
		}
		if (Keyboard::isKeyPressed(Keyboard::Num9) || Keyboard::isKeyPressed(Keyboard::Numpad9))
		{
			input.stringValue += '9';
		}
	}
	if (!sudokuPlayer[positionCursor / SIZE][positionCursor % SIZE])
	{
		if (Keyboard::isKeyPressed(Keyboard::Return))
		{
			input.intValue = atoi(input.stringValue.c_str());

			bool correct;

			correct = checkColumn(	positionCursor%SIZE, input.intValue) 
									&& checkRow(positionCursor/SIZE, input.intValue) 
									&& checkSquare(positionCursor / SIZE, positionCursor % SIZE, input.intValue);

			if (input.intValue > 0 && input.intValue <= SIZE && correct)
			{
				sudokuView[positionCursor / SIZE][positionCursor % SIZE] = input.intValue;
				input.stringValue = "";
			}
			else
			{
				input.stringValue = "";
			}
		}
	}
}

