#include "Input.h"
#include "ProgramState.h"
#include "ArrayState.h"
#include "StaticSprite.h"
#include <string.h>
#include <SFML/Graphics.hpp>

class arraySizeMenu
{
public:
	arraySizeMenu(sf::RenderWindow * hwnd, Input * in);
	~arraySizeMenu();

	void handleInput(float dt);
	void update(float dt);
	void render();
	void moveUp();
	void moveDown();
	int getSelectedOption() { return optionSelected; };
	ArrayState getArrayState();
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

	//Variables used for array menu background and options
	ProgramState actualState;
	ArrayState arrayState;
	StaticSprite sprite;
	sf::Texture texture;
	sf::Text menu[6];
	int optionSelected;
	int maxItems;
};

