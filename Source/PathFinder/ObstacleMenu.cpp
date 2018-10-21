#include "ObstacleMenu.h"

ObstacleMenu::ObstacleMenu(sf::RenderWindow * hwnd, Input * in)
{
	window = hwnd;
	input = in;
	state = ProgramState::MENU;
	sf::Vector2f position(window->getSize());
	position.x = position.x / 2.0f;

	//Menu option1 text
	font.loadFromFile("../font/Digital_tech.otf");
	menu[0].setFont(font);
	menu[0].setFillColor(sf::Color::Black);
	menu[0].setCharacterSize(32);
	menu[0].setPosition(position.x - 85, (position.y / 2) * 1.0f);
	menu[0].setString("No Obstacle");

	//Menu option2 text
	menu[1].setFont(font);
	menu[1].setFillColor(sf::Color::White);
	menu[1].setCharacterSize(32);
	menu[1].setPosition(position.x - 110, (position.y / 2) * 1.15f);
	menu[1].setString("Small Obstacle");

	//Menu option3 text
	menu[2].setFont(font);
	menu[2].setFillColor(sf::Color::White);
	menu[2].setCharacterSize(32);
	menu[2].setPosition(position.x - 110, (position.y / 2) * 1.30f);
	menu[2].setString("Large Obstacle");

	//Menu option4 text
	menu[3].setFont(font);
	menu[3].setFillColor(sf::Color::White);
	menu[3].setCharacterSize(32);
	menu[3].setPosition(position.x - 160, (position.y / 2) * 1.45f);
	menu[3].setString("Surrounding Obstacle");

	//Menu option5 text
	menu[4].setFont(font);
	menu[4].setFillColor(sf::Color::White);
	menu[4].setCharacterSize(32);
	menu[4].setPosition(position.x - 100, (position.y / 2) * 1.6f);
	menu[4].setString("Even Obstacle");

	//Menu option6 text
	menu[5].setFont(font);
	menu[5].setFillColor(sf::Color::White);
	menu[5].setCharacterSize(32);
	menu[5].setPosition(position.x - 45, (position.y / 2) * 1.75f);
	menu[5].setString("Go Back");

	//Menu graphic
	texture.loadFromFile("../gfx/background.png");
	sprite.setTexture(&texture);
	sprite.setPosition(-20, 0);
	sprite.setOrigin(sprite.getSize() / 2.0f);
	sprite.setSize(sf::Vector2f(858, 831));

	//Initialise selection variables
	optionSelected = 0;
	maxItems = 6;
}

ObstacleMenu::~ObstacleMenu()
{
}
/**Handles user input on obstacle menu screen*/
void ObstacleMenu::handleInput(float dt)
{
	//Set obstacle state
	obstacleState = ProgramState::OBSTACLEMENU;

	//Gets selected option and changes to that program/obstacle state
	if (input->isKeyDown(sf::Keyboard::Return))
	{
		input->setKeyUp(sf::Keyboard::Return);
		switch (getSelectedOption())
		{
		case 0: obstacleState = ProgramState::NONE;
			state = actualState;
			break;
		case 1: obstacleState = ProgramState::SMALL;
			state = actualState;
			break;
		case 2: obstacleState = ProgramState::LARGE;
			state = actualState;
			break;
		case 3: obstacleState = ProgramState::SURROUNDING;
			state = actualState;
			break;
		case 4: obstacleState = ProgramState::EVEN;
			state = actualState;
			break;
		case 5: obstacleState = ProgramState::MENU;
			state = ProgramState::MENU;
			break;
		}
	}
	else
	{
		state = ProgramState::OBSTACLEMENU;
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

/**Updates obstacle menu*/
void ObstacleMenu::update(float dt)
{
}

/**Renders menu to screen*/
void ObstacleMenu::render()
{
	beginDraw();
	//Draw background
	window->draw(sprite);
	//Draw menu options
	for (int i = 0; i < 6; i++)
	{
		window->draw(menu[i]);
	}
	endDraw();
}

/**Moves up menu options*/
void ObstacleMenu::moveUp()
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
void ObstacleMenu::moveDown()
{
	//Checks whether you can move down the menu and allows it if this is the case
	if (optionSelected + 1 < maxItems)
	{
		menu[optionSelected].setFillColor(sf::Color::White);
		optionSelected++;
		menu[optionSelected].setFillColor(sf::Color::Black);
	}
}

/**Sets actual state*/
void ObstacleMenu::setActualState(ProgramState actState)
{
	actualState = actState;
}

/**Updates actual state*/
ProgramState ObstacleMenu::getState()
{
	return state;
}

/**Updates obstacle state*/
ProgramState ObstacleMenu::getObstacleState()
{
	return obstacleState;
}

/**Clears window for drawing*/
void ObstacleMenu::beginDraw()
{
	window->clear(sf::Color::Black);
}

/**Draws sprites and text*/
void ObstacleMenu::endDraw()
{
	window->display();
}