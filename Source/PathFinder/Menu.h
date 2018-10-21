#include "Input.h"
#include "ProgramState.h"
#include "StaticSprite.h"
#include <string.h>
#include <SFML/Graphics.hpp>

class Menu
{
public:
	Menu(sf::RenderWindow* hwnd, Input * in);
	~Menu();

	void handleInput(float dt);
	void update(float dt);
	void render();
	void moveUp();
	void moveDown();
	int getSelectedOption() { return optionSelected; };
	ProgramState getObstacleState();
	ProgramState getState();

private:
	void beginDraw();
	void endDraw();

	//Window
	sf::RenderWindow* window;
	//Input
	Input* input;
	//Font
	sf::Font font;

	//Variables used for menu background and options
	ProgramState obstacleState, actualState;
	StaticSprite sprite;
	sf::Texture texture;
	sf::Text menu[4];
	int optionSelected;
	int maxItems;
};
