#include "Menu.h"



Menu::Menu(sf::RenderWindow * hwnd, Input * in)
{	
	//Window and input
	window = hwnd;
	input = in;
	//Program state
	actualState = ProgramState::MENU;
	//Text position
	sf::Vector2f position(window->getSize());
	position.x = position.x / 2.0f;

	//Menu option1 text
	font.loadFromFile("../font/Digital_tech.otf");
	menu[0].setFont(font);
	menu[0].setFillColor(sf::Color::Black);
	menu[0].setCharacterSize(32);
	menu[0].setPosition(position.x - 120, (position.y / 2) * 1.0f);
	menu[0].setString("View Step By Step");

	//Menu option2 text
	menu[1].setFont(font);
	menu[1].setFillColor(sf::Color::White);
	menu[1].setCharacterSize(32);
	menu[1].setPosition(position.x - 72.5, (position.y / 2) * 1.25f);
	menu[1].setString("Skip to End");

	//Menu option3 text
	menu[2].setFont(font);
	menu[2].setFillColor(sf::Color::White);
	menu[2].setCharacterSize(32);
	menu[2].setPosition(position.x - 95, (position.y / 2) * 1.5f);
	menu[2].setString("Set Array Size");

	//Menu option4 text
	menu[3].setFont(font);
	menu[3].setFillColor(sf::Color::White);
	menu[3].setCharacterSize(32);
	menu[3].setPosition(position.x - 20, (position.y / 2) * 1.75f);
	menu[3].setString("Exit");

	//Menu graphic
	texture.loadFromFile("../gfx/background.png");
	sprite.setTexture(&texture);
	sprite.setPosition(-20, 0);
	sprite.setOrigin(sprite.getSize() / 2.0f);
	sprite.setSize(sf::Vector2f(858, 831));

	//Initialise selection variables
	optionSelected = 0;
	maxItems = 4;
}

Menu::~Menu()
{
}

/**Handles user input on menu screen*/
void Menu::handleInput(float dt)
{
	//Gets selected option and changes to obstacle menu
	if (input->isKeyDown(sf::Keyboard::Return))
	{
		input->setKeyUp(sf::Keyboard::Return);
		switch (getSelectedOption())
		{
		case 0: actualState = ProgramState::OBSTACLEMENU;
			obstacleState = ProgramState::STEP;
			break;
		case 1: actualState = ProgramState::OBSTACLEMENU;
			obstacleState = ProgramState::SKIP;
			break;
		case 2: actualState = ProgramState::ARRAYMENU;
			obstacleState = ProgramState::SKIP;
			break;
		case 3: window->close();
			break;
		}
	}
	else
	{
		actualState = ProgramState::MENU;
	}

	//If up key is pressed cycle up 
	if (input->isKeyDown(sf::Keyboard::Up))
	{
		input->setKeyUp(sf::Keyboard::Up);
		moveUp();
	}
	//If down key is pressed cycle down 
	if (input->isKeyDown(sf::Keyboard::Down))
	{
		input->setKeyUp(sf::Keyboard::Down);
		moveDown();
	}
}

/**Updates menu*/
void Menu::update(float dt)
{
}

/**Renders menu to screen*/
void Menu::render()
{
	beginDraw();
	//Draw background
	window->draw(sprite);
	//Draw menu options
	for (int i = 0; i < 4; i++)
	{
		window->draw(menu[i]);
	}
	endDraw();
}

/**Moves up menu options*/
void Menu::moveUp()
{
	//Checks whether you can move up the menu and allows it if this is the case
	if (optionSelected - 1 >= 0)
	{
		menu[optionSelected].setFillColor(sf::Color::White);
		optionSelected--;
		menu[optionSelected].setFillColor(sf::Color::Black);
	}
}

/**Moves down menu options*/
void Menu::moveDown()
{
	//Checks whether you can move down the menu and allows it if this is the case
	if (optionSelected + 1 < maxItems)
	{
		menu[optionSelected].setFillColor(sf::Color::White);
		optionSelected++;
		menu[optionSelected].setFillColor(sf::Color::Black);
	}
}

/**Returns obstacle state*/
ProgramState Menu::getObstacleState()
{
	return obstacleState;
}

/**Updates actual state*/
ProgramState Menu::getState()
{
	return actualState;
}

/**Clears window for drawing*/
void Menu::beginDraw()
{
	window->clear(sf::Color::Black);
}

/**Draws sprites and text*/
void Menu::endDraw()
{
	window->display();
}


