#include "SudokuGame.h"


RenderWindow window(VideoMode(SIZE_H, SIZE_V), "Sudoku", Style::Close);


SudokuGame::SudokuGame()
{
	//state = GameState::END;

	font.loadFromFile("Black-Acute.ttf");


	state = GameState::MENU;
}


SudokuGame::~SudokuGame()
{
}
void SudokuGame::menu()
{
	//window.setFramerateLimit(60);
	Texture backgroundTexture;
	backgroundTexture.loadFromFile("Background.jpg");
	Sprite background(backgroundTexture);
	Text title(L"Судоку", font, 80);
	title.setStyle(Text::Bold);
	title.setPosition(SIZE_H / 2 - title.getGlobalBounds().width / 2, 60);
	const int numWords = 2;
	Text textMenu[numWords];
	textMenu[0].setString(L"Игра");
	textMenu[1].setString(L"Выход");
	for (int i = 0; i < numWords; i++)
	{
		textMenu[i].setFont(font);
		textMenu[i].setCharacterSize(65);
		textMenu[i].setPosition(SIZE_H / 2 - textMenu[i].getGlobalBounds().width / 2, 200 + i * 120);
	}
	while (state == GameState::MENU)
	{
		Vector2f mouse(Mouse::getPosition(window));
		Event event;

		while (window.pollEvent(event))
		{
			
			if (event.type == Event::Closed || event.type == Event::KeyPressed &&
				event.key.code == Keyboard::Escape)
				state = GameState::END;

		                                     
			else if (textMenu[0].getGlobalBounds().contains(mouse) &&
				event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
			{
				state = GameState::GAME;
			}

			
			else if (textMenu[1].getGlobalBounds().contains(mouse) &&
				event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
			{
				state = GameState::END;
			}
		}
		for (int i = 0; i < numWords; i++)
			if (textMenu[i].getGlobalBounds().contains(mouse))
				textMenu[i].setFillColor(Color::Red);
			else textMenu[i].setFillColor(Color::White);
		window.clear();
		window.draw(background);
		window.draw(title);
		for (int i = 0; i < numWords; i++)
			window.draw(textMenu[i]);
		window.display();
	}
}

void SudokuGame::levels()
{
	Texture backgroundTexture;
	backgroundTexture.loadFromFile("Background.jpg");
	Sprite background(backgroundTexture);
	Text title(L"Уровень сложности", font, 90);
	title.setStyle(Text::Bold);
	title.setPosition(SIZE_H / 2 - title.getGlobalBounds().width / 2, 30);
	title.setStyle(Text::Bold);
	std::string easy, medium, hard;
	const int numberWords = 4;
	Text text[numberWords];
	text[0].setString(L"Лёгкий");
	text[1].setString(L"Средний");
	text[2].setString(L"Сложный");
	text[3].setString(L"Вернуться");

	for (int i = 0; i < numberWords; i++)
	{
		text[i].setFont(font);
		text[i].setCharacterSize(65);
		text[i].setPosition(SIZE_H / 2 - text[i].getGlobalBounds().width / 2, 150 + i * 120);
	}

	while (state == GameState::GAME && window.isOpen())
	{
		Vector2f mouse(Mouse::getPosition(window));
		Event event;
		SudokuEngine engine;

		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();

			if (text[0].getGlobalBounds().contains(mouse) && event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
			{
				if (engine.runEngine(window, 0))
					state = GameState::GAME;
				else
					state = GameState::MENU;
			}

			else if (text[1].getGlobalBounds().contains(mouse) && event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
			{
				if (engine.runEngine(window, 1))
					state = GameState::GAME;
				else
					state = GameState::MENU;
			}

			else if (text[2].getGlobalBounds().contains(mouse) && event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
			{
				if (engine.runEngine(window, 2))
					state = GameState::GAME;
				else
					state = GameState::MENU;
			}

			else if (text[3].getGlobalBounds().contains(mouse) && event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
			{
				state = GameState::MENU;
			}
		}

		for (int i = 0; i < numberWords; i++)
			if (text[i].getGlobalBounds().contains(mouse))
				text[i].setFillColor(Color::Red);
			else text[i].setFillColor(Color::White);


		window.clear();
		window.draw(background);
		window.draw(title);
		for (int i = 0; i < numberWords; i++)
			window.draw(text[i]);
		window.display();
	}
}


void SudokuGame::runGame()
{
	while (state != GameState::END)
	{
		switch (state)
		{
		case GameState::MENU:
			menu();
			break;
		case GameState::GAME:
			levels();
			break;
		}
	}
}
