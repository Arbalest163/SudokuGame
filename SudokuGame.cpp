#include "SudokuGame.h"
#define SIZE_H 1920
#define SIZE_V 1080

RenderWindow window(VideoMode(SIZE_H, SIZE_V), "Sudoku", Style::Close);

void SudokuGame::menu()
{
	//window.setFramerateLimit(60);
	Text title("Sudoku", font, 80);
	title.setStyle(Text::Bold);

	title.setPosition(SIZE_H / 2 - title.getGlobalBounds().width / 2, 60);

	const int numWords = 2;

	Text tekst[numWords];

	std::string str[] = { "Play", "Exit" };
	for (int i = 0; i < numWords; i++)
	{
		tekst[i].setFont(font);
		tekst[i].setCharacterSize(65);

		tekst[i].setString(str[i]);
		tekst[i].setPosition(SIZE_H / 2 - tekst[i].getGlobalBounds().width / 2, 200 + i * 120);
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

		                                     
			else if (tekst[0].getGlobalBounds().contains(mouse) &&
				event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
			{
				state = GameState::GAME;
			}

			
			else if (tekst[1].getGlobalBounds().contains(mouse) &&
				event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
			{
				state = GameState::END;
			}
		}
		for (int i = 0; i < numWords; i++)
			if (tekst[i].getGlobalBounds().contains(mouse))
				tekst[i].setFillColor(Color::Red);
			else tekst[i].setFillColor(Color::White);

		window.clear();

		window.draw(title);
		for (int i = 0; i < numWords; i++)
			window.draw(tekst[i]);

		window.display();
	}
}

void SudokuGame::levels()
{
	sf::Text title(L"Уровень сложности", font, 90);
	title.setStyle(sf::Text::Bold);

	title.setPosition(SIZE_H / 2 - title.getGlobalBounds().width / 2, 30);
	title.setStyle(sf::Text::Bold);

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
		Vector2f mouse(sf::Mouse::getPosition(window));
		Event event;
		SudokuEngine engine;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (text[0].getGlobalBounds().contains(mouse) && event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
			{
				if (engine.runEngine(window, 0))
					state = GameState::GAME;
				else
					state = GameState::MENU;
			}

			else if (text[1].getGlobalBounds().contains(mouse) && event.type == sf::Event::MouseButtonReleased && event.key.code == sf::Mouse::Left)
			{
				if (engine.runEngine(window, 1))
					state = GameState::GAME;
				else
					state = GameState::MENU;
			}

			else if (text[2].getGlobalBounds().contains(mouse) && event.type == sf::Event::MouseButtonReleased && event.key.code == sf::Mouse::Left)
			{
				if (engine.runEngine(window, 2))
					state = GameState::GAME;
				else
					state = GameState::MENU;
			}

			else if (text[3].getGlobalBounds().contains(mouse) && event.type == sf::Event::MouseButtonReleased && event.key.code == sf::Mouse::Left)
			{
				state = GameState::MENU;
			}
		}

		for (int i = 0; i < numberWords; i++)
			if (text[i].getGlobalBounds().contains(mouse))
				text[i].setFillColor(Color::Red);
			else text[i].setFillColor(Color::White);


		window.clear();
		window.draw(title);
		for (int i = 0; i < numberWords; i++)
			window.draw(text[i]);
		window.display();
	}
}

SudokuGame::SudokuGame()
{
	state = GameState::END;

	if (!font.loadFromFile("Black-Acute.ttf"))
		return;

	state = GameState::MENU;
}


SudokuGame::~SudokuGame()
{
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
