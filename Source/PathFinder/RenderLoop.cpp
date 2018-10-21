#include "RenderLoop.h"

RenderLoop::RenderLoop(sf::RenderWindow* hwnd, Input* dnwh)
{
	//Window and drawing variables
	window = hwnd;
	input = dnwh;
	state = ProgramState::STEP;
	skipSpeed = 0.05;

	//reset map
	level.resetMap();

}

RenderLoop::~RenderLoop()
{

}

/** Updates core data*/
void RenderLoop::update(float dt)
{
	//If we're not in menu
	if (state != ProgramState::MENU) {
		if (counter == 0) {
			//Calculate A* path and return steps
			Apath = astar.aStar(start, goal, 1);
			Alist = astar.getList();
			//Calculate Dijkstra path and return steps
			Dpath = astar.aStar(start, goal, 0);
			Dlist = astar.getList();
			//Reset coords and neighbours for next obstacle choice
			astar.resetCoordsAndNeighbours();
			counter++;
		}
	}

	else {
		counter = 0;	//Resets counter if ESC is pressed and menu reopened
	}

	//Colours each tile either per frame, or all it once
	stepOrSkip(dt, Alist, Apath, 'a');
	stepOrSkip(dt, Dlist, Dpath, 'd');
}

/** Handles user input*/
void RenderLoop::handleInput()
{
	//Checks whether ESC has been pressed and returns to menu if it has been
	if (input->isKeyDown(sf::Keyboard::Escape))
	{
		restart = !restart;
	
		if (restart == true) {
			input->setKeyUp(sf::Keyboard::Escape);
			state = ProgramState::MENU;
			level.resetMap();
			steps.reset();
			Alist.clear();
			Dlist.clear();
		}

	}
}

/** Renders drawable sprites and text to screen*/
void RenderLoop::render()
{
	beginDraw();
	//Draw map
	level.render(window);
	//Set HUD view
	window->setView(window->getDefaultView());
	//Draw steps
	steps.render(window);
	endDraw();

}

/** Either updates map per frame or all at once*/
void RenderLoop::stepOrSkip(float dt, std::list<Coords> &list, std::list<Coords> &path, char key)
{	
	//Variables for stepping 
	delta = dt;

	//Variables for skipping
	std::list<Coords>::const_iterator iterator;

	switch (state)
	{
	case (ProgramState::SKIP):
		//Loops over each visited item and alters its map color
		for (iterator = list.begin(); iterator != list.end(); ++iterator) {								
			Coords temp = *iterator;
			if ((temp.x == goal.x && temp.y == goal.y) || (temp.x == start.x && temp.y == start.y)) {
				continue;
			}
			level.updateMap(temp.x, temp.y, key, sf::Color::Red);
			steps.update(key);
		}
		//Loops over each item in path and alters its map color
		for (auto const& v : path) {
			Coords temp = v;
			if ((temp.x == goal.x && temp.y == goal.y) || (temp.x == start.x && temp.y == start.y)) {
				continue;
			}
			level.updateMap(temp.x, temp.y, key, sf::Color::White);
			steps.update(key);
		}
		//Clears boths lists 
		list.clear();
		path.clear();
		break;
	case (ProgramState::STEP):

		//Increment time  
		elapsedTime += dt;

		//If enough time has passed move onto next step 
		if (elapsedTime >= skipSpeed){
			//If list is not empty, alter tile map color and reset time
			if (!list.empty()) {
				Coords temp = list.back();
				list.pop_back();
				if ((temp.x == goal.x && temp.y == goal.y) || (temp.x == start.x && temp.y == start.y)) {
					
				}
				else {
					level.updateMap(temp.x, temp.y, key, sf::Color::Red);
					elapsedTime = 0;
					steps.update(key);
				}

			}
			//If list is empth and path is not, alter tile map color and reset time
			if (list.empty() && !path.empty()) {
			
				Coords temp = path.back();
				path.pop_back();
				if ((temp.x == goal.x && temp.y == goal.y) || (temp.x == start.x && temp.y == start.y)) {
					
				}
				else {
					level.updateMap(temp.x, temp.y, key, sf::Color::White);
					elapsedTime = 0;
					steps.update(key);
				}
			}

		}
		break;
	}
}

/** Deals with window resizing*/
void RenderLoop::reziseView(float VIEW_HEIGHT, float VIEW_WIDTH, sf::View & view)
{
	//Define aspect ratio 
	float aspectRatio = float(window->getSize().x) / float(window->getSize().y);
	view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_WIDTH);
}

/** Returns current Program state*/
ProgramState RenderLoop::getState()
{
	return state;
}

/** Sets Program state*/
void RenderLoop::setState(ProgramState newstate)
{
	state = newstate;
}

/** Sets obstacle state and alters required variables*/
void RenderLoop::setObstacle(ProgramState obst)
{
	//Resets map to clear old start and goal tiles and sets new positions/colors
	if (obst == ProgramState::EVEN) {
		level.resetMap();
		goal.x = 6; goal.y = (A - 1); level.updateMap(goal.x, goal.y, 'a', sf::Color(248, 131, 121));
		start.x = 6; start.y = 0; level.updateMap(start.x, start.y, 'a', sf::Color(254, 216, 177));
		goal.x = 6; goal.y = (A - 1); level.updateMap(goal.x, goal.y, 'd', sf::Color(248, 131, 121));
		start.x = 6; start.y = 0; level.updateMap(start.x, start.y, 'd', sf::Color(254, 216, 177));
	}
	//Sets start and goal positions/colors
	else{
		goal.x = 0; goal.y = (A - 1); level.updateMap(goal.x, goal.y, 'a', sf::Color(248, 131, 121));
		start.x = (A - 5); start.y = 6; level.updateMap(start.x, start.y, 'a', sf::Color(254, 216, 177));
		goal.x = 0; goal.y = (A - 1); level.updateMap(goal.x, goal.y, 'd', sf::Color(248, 131, 121));
		start.x = (A - 5); start.y = 6; level.updateMap(start.x, start.y, 'd', sf::Color(254, 216, 177));
	} 
	//Sets blocked tiles color and updates grid
	level.setBlocked(obst);
	astar.setBlocked(obst);
}

/**Updates map and pathfinding grid size*/
void RenderLoop::setArraySize(ArrayState array)
{
	//Variables to store desired chnage to grid size
	int x;
	float size;

	//Assigns grid size
	switch (array) {
	case ArrayState::ONE:
		x = 15;
		size = 30.0f;
		break;
	case ArrayState::TWO:
		x = 30;
		size = 15.0f;
		break;
	case ArrayState::THREE:
		x = 45;
		size = 10.0f;
		break;
	case ArrayState::FOUR:
		x = 60;
		size = 7.5f;
		break;
	case ArrayState::FIVE:
		x = 75;
		size = 6.0f;
		break;
	}

	A = x;
	astar.setArraySize(x);
	level.setArraySize(x, size);
	level.init();
}

/** Clears window for drawing*/
void RenderLoop::beginDraw()
{
	window->clear(sf::Color(128, 128, 128));
}

/** Display text and sprites*/
void RenderLoop::endDraw()
{
	window->display();
}
