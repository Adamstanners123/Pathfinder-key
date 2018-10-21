#include "StaticSprite.h"
#include <SFML/Graphics.hpp> 
#include <sstream>

class StepsAndKey :
	public StaticSprite
{
public:
	StepsAndKey();
	~StepsAndKey();

	void reset();
	void update(char key);
	void render(sf::RenderWindow* window);

protected:

	//Font
	sf::Font font;

	//Stuff for map key
	sf::RectangleShape key[6];
	sf::Text keyText[6];

	//Stuff for steps counter
	sf::Text Atext, Dtext;
	float Asteps, Dsteps;
};

