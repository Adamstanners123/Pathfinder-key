#include <SFML/Graphics.hpp>
#include "Input.h"
#include <string.h>
#include "ProgramState.h"
#include "StaticSprite.h"

class ObstacleMenu
{
public:
	ObstacleMenu(sf::RenderWindow* hwnd, Input * in);
	~ObstacleMenu();

	void handleInput(float dt);
	void update(float dt);
	void render();
	void moveUp();
	void moveDown();
	void setActualState(ProgramState actState);
	int getSelectedOption() { return optionSelected; };
	ProgramState getState();
	ProgramState getObstacleState();

private:
	void beginDraw();
	void endDraw();

	//Window
	sf::RenderWindow* window;
	//Input
	Input* input;
	//Font
	sf::Font font;

	//Variables used for obstacle menu background and options
	ProgramState obstacleState, actualState, state;
	StaticSprite sprite;
	sf::Texture texture;
	sf::Text menu[6];
	int optionSelected;
	int maxItems;
};

