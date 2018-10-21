#include "arraySizeMenu.h"




arraySizeMenu::arraySizeMenu(sf::RenderWindow * hwnd, Input * in)
{
	//Window and input
	window = hwnd;
	input = in;
	//Program state
	actualState = ProgramState::ARRAYMENU;
	//Text position
	sf::Vector2f position(window->getSize());
	position.x = position.x / 2.0f;

	//Menu option1 text
	font.loadFromFile("../font/Digital_tech.otf");
	menu[0].setFont(font);
	menu[0].setFillColor(sf::Color::Black);
	menu[0].setCharacterSize(32);
	menu[0].setPosition(position.x - 130, (position.y / 2) * 1.0f);
	menu[0].setString("Array Size 1 - 15 x 15");

	//Menu option2 text
	menu[1].setFont(font);
	menu[1].setFillColor(sf::Color::White);
	menu[1].setCharacterSize(32);
	menu[1].setPosition(position.x - 150, (position.y / 2) * 1.15f);
	menu[1].setString("Array Size 2 - 30 x 30");

	//Menu option3 text
	menu[2].setFont(font);
	menu[2].setFillColor(sf::Color::White);
	menu[2].setCharacterSize(32);
	menu[2].setPosition(position.x - 150, (position.y / 2) * 1.30f);
	menu[2].setString("Array Size 3 - 45 x 45");

	//Menu option4 text
	menu[3].setFont(font);
	menu[3].setFillColor(sf::Color::White);
	menu[3].setCharacterSize(32);
	menu[3].setPosition(position.x - 150, (position.y / 2) * 1.45f);
	menu[3].setString("Array Size 4 - 60 x 60");

	//Menu option5 text
	menu[4].setFont(font);
	menu[4].setFillColor(sf::Color::White);
	menu[4].setCharacterSize(32);
	menu[4].setPosition(position.x - 150, (position.y / 2) * 1.6f);
	menu[4].setString("Array Size 5 - 75 x 75");

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

arraySizeMenu::~arraySizeMenu()
{
}

/**Handles user input on array menu screen*/
void arraySizeMenu::handleInput(float dt)
{
	//Gets selected option and changes back to menu
	if (input->isKeyDown(sf::Keyboard::Return))
	{
		input->setKeyUp(sf::Keyboard::Return);
		switch (getSelectedOption())
		{
		case 0: actualState = ProgramState::MENU;
			arrayState = ArrayState::ONE;
			break;
		case 1: actualState = ProgramState::MENU;
			arrayState = ArrayState::TWO;
			break;
		case 2: actualState = ProgramState::MENU;
			arrayState = ArrayState::THREE;
			break;
		case 3: actualState = ProgramState::MENU;
			arrayState = ArrayState::FOUR;
			break;
		case 4: actualState = ProgramState::MENU;
			arrayState = ArrayState::FIVE;
			break;
		case 5: actualState = ProgramState::MENU;;
			break;
		}
	}
	else
	{
		actualState = ProgramState::ARRAYMENU;
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

/**Updates array menu*/
void arraySizeMenu::update(float dt)
{

}

/**Renders array menu to screen*/
void arraySizeMenu::render()
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

/**Moves up array menu options*/
void arraySizeMenu::moveUp()
{
	//Checks whether you can move up the array menu and allows it if this is the case
	if (optionSelected - 1 >= 0)
	{
		menu[optionSelected].setFillColor(sf::Color::White);
		optionSelected--;
		menu[optionSelected].setFillColor(sf::Color::Black);
	}
}

/**Moves down array menu options*/
void arraySizeMenu::moveDown()
{
	//Checks whether you can move down the array menu and allows it if this is the case
	if (optionSelected + 1 < maxItems)
	{
		menu[optionSelected].setFillColor(sf::Color::White);
		optionSelected++;
		menu[optionSelected].setFillColor(sf::Color::Black);
	}
}

/**Returns array state*/
ArrayState arraySizeMenu::getArrayState()
{
	return arrayState;
}

/**Returns actual state*/
ProgramState arraySizeMenu::getState()
{
	return actualState;
}

/**Clears window for drawing*/
void arraySizeMenu::beginDraw()
{
	window->clear(sf::Color::Black);
}

/**Draws sprites and text*/
void arraySizeMenu::endDraw()
{
	window->display();
}

