#include "RenderLoop.h" 
#include "Input.h"
#include "Menu.h"
#include "ObstacleMenu.h"
#include "arraySizeMenu.h"
#include "ArrayState.h"
#include "ProgramState.h"	
#include <iostream>
using namespace std;

float VIEW_HEIGHT = 600.0f;
float VIEW_WIDTH = 800.0f;

void main(int argc, char** argv[]) {

	//Winow settings
	sf::RenderWindow window(sf::VideoMode(800, 600), "Dijkstra vs A*!", sf::Style::Close | sf::Style::Resize);
	sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(VIEW_WIDTH, VIEW_HEIGHT));
	//Main classes
	Input input;
	RenderLoop loop(&window, &input);
	Menu menu(&window, &input);
	ObstacleMenu obstacleMenu(&window, &input);
	arraySizeMenu arrayMenu(&window, &input);
	//Set initial state
	ProgramState state = ProgramState::MENU;
	ArrayState arrayState = ArrayState::ONE;
	//For delta time
	sf::Clock clock;
	float deltaTime;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				//Close window
				window.close();
				break;
			case sf::Event::Resized:
				//Resize window
				loop.reziseView(VIEW_HEIGHT, VIEW_WIDTH, view);
				break;
			case sf::Event::KeyPressed:
				//Update input class
				input.setKeyDown(event.key.code);
				break;
			case sf::Event::KeyReleased:
				//Update input class
				input.setKeyUp(event.key.code);
				break;
			default:
				//Don't handle other events  
				break;
			}
		}

		// Calculate delta time. How much time has passed
		// Since it was last calculated (in seconds) and restart the clock
		deltaTime = clock.restart().asSeconds();


		//Switch between program states
		switch (state)
		{
		case (ProgramState::MENU):
			menu.handleInput(deltaTime);
			menu.update(deltaTime);
			menu.render();
			state = menu.getState();
			loop.setState(state);
			if (state != ProgramState::MENU) {
				loop.setArraySize(arrayState);
			}
			break;
		case (ProgramState::OBSTACLEMENU):
			obstacleMenu.setActualState(menu.getObstacleState());
			obstacleMenu.handleInput(deltaTime);
			obstacleMenu.update(deltaTime);
			obstacleMenu.render();
			loop.setObstacle(obstacleMenu.getObstacleState());
			state = obstacleMenu.getState();
			loop.setState(state);
			break;
		case (ProgramState::ARRAYMENU):
			arrayMenu.handleInput(deltaTime);
			arrayMenu.update(deltaTime);
			arrayMenu.render();
			arrayState = arrayMenu.getArrayState();
			state = arrayMenu.getState();
			loop.setState(state);
			break;
		case (ProgramState::SKIP):
			loop.handleInput();
			loop.update(deltaTime);
			window.setView(view);
			loop.render();
			state = loop.getState();
			break;
		case (ProgramState::STEP):
			loop.handleInput();
			loop.update(deltaTime);
			window.setView(view);
			loop.render();
			state = loop.getState();
			break;
		default: 
			break;
		}
	}
}
