#pragma once 
#include "Input.h"
#include "Map.h"
#include "Steps.h"
#include "ProgramState.h"
#include "ArrayState.h"
#include "Astar.h"
#include <SFML/Graphics.hpp> 

class RenderLoop {
public:  RenderLoop(sf::RenderWindow* hwnd, Input* dnwh);
		 ~RenderLoop();

		 void handleInput();
		 void update(float dt);
		 void render();
		 void stepOrSkip(float dt, std::list<Coords> &list, std::list<Coords> &path, char key);
		 void reziseView(float VIEW_HEIGHT, float VIEW_WIDTH, sf::View& view);
		 ProgramState getState();
		 void setState(ProgramState state);
		 void setObstacle(ProgramState obst);
		 void setArraySize(ArrayState array);

private:
	void beginDraw();
	void endDraw();

	//Window
	sf::RenderWindow* window;

	//Input and Map classes
	Input* input;
	Map level;

	//Stuff for skipping/animating 
	float elapsedTime;
	float delta;
	float skipSpeed;
	//Stuff for menus/display
	StepsAndKey steps;
	ProgramState state;
	bool restart = false;
	int counter = 0;
	//Stuff for pathfinding/drawing
	int A;
	Astar astar;
    Coords start, goal;
	list<Coords> Alist, Apath, Dlist, Dpath;


};

