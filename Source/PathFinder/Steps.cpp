#include "Steps.h"



StepsAndKey::StepsAndKey()
{
	//Initialise A* step counter attributes
	font.loadFromFile("../font/Digital_tech.otf");
	Atext.setFont(font);
	Atext.setPosition(10, 350);
	Atext.setCharacterSize(10);
	Atext.setFillColor(sf::Color::Black);

	//Initialise Dijkstra step counter attributes
	Dtext.setFont(font);
	Dtext.setPosition(475, 350);
	Dtext.setCharacterSize(10);
	Dtext.setFillColor(sf::Color::Black);

	//Initialise key shape attributes
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 3; j++) {
			key[j + (i* 3)].setSize(sf::Vector2f(40, 40));
			key[j + (i * 3)].setOutlineThickness(1);
			key[j + (i * 3)].setOutlineColor(sf::Color::Black);
			key[j + (i * 3)].setPosition(20 + (i * 180) , 400 + (j * 55));
		}
	}
	
	//Intialise "unexplored" key attributes
	key[0].setFillColor(sf::Color(192, 192, 192));
		keyText[0].setFont(font);
		keyText[0].setPosition(65, 415);
		keyText[0].setCharacterSize(10);
		keyText[0].setString("Unexplored");
		keyText[0].setFillColor(sf::Color::Black);
	//Intialise "explored" key attributes
	key[1].setFillColor(sf::Color::Red);
		keyText[1].setFont(font);
		keyText[1].setPosition(65, 470);
		keyText[1].setCharacterSize(10);
		keyText[1].setString("Explored");
		keyText[1].setFillColor(sf::Color::Black);
	//Intialise "obstacle" key attributes
	key[2].setFillColor(sf::Color::Black);
		keyText[2].setFont(font);
		keyText[2].setPosition(65, 525);
		keyText[2].setCharacterSize(10);
		keyText[2].setString("Obstacle");
		keyText[2].setFillColor(sf::Color::Black);
	//Intialise "start" key attributes
	key[3].setFillColor(sf::Color(254, 216, 177));
		keyText[3].setFont(font);
		keyText[3].setPosition(245, 415);
		keyText[3].setCharacterSize(10);
		keyText[3].setString("Start");
		keyText[3].setFillColor(sf::Color::Black);
	//Intialise "goal" key attributes
	key[4].setFillColor(sf::Color(248, 131, 121));
		keyText[4].setFont(font);
		keyText[4].setPosition(245, 470);
		keyText[4].setCharacterSize(10);
		keyText[4].setString("Goal");
		keyText[4].setFillColor(sf::Color::Black);
	//Intialise "path" key attributes
	key[5].setFillColor(sf::Color::White);
		keyText[5].setFont(font);
		keyText[5].setPosition(245, 525);
		keyText[5].setCharacterSize(10);
		keyText[5].setString("Path");
		keyText[5].setFillColor(sf::Color::Black);


}


StepsAndKey::~StepsAndKey()
{
}

/**Resets step counters*/
void StepsAndKey::reset()
{
	Asteps = 0;
	Dsteps = 0;
}

/**Updates steps counters*/
void StepsAndKey::update(char key)
{
	//Update A* steps
	if (key == 'a') {
		Asteps++;
		std::ostringstream AstepsSS;
		AstepsSS << "A* Steps : " << Asteps;
		Atext.setString(AstepsSS.str());
	}
	//Update dijkstra steps
	if (key == 'd') {
		Dsteps++;
		std::ostringstream DstepsSS;
		DstepsSS << "Dijkstra Steps : " << Dsteps;
		Dtext.setString(DstepsSS.str());
	}
}

/**Renders step counter and key to screen*/
void StepsAndKey::render(sf::RenderWindow * window)
{
	window->draw(Atext);
	window->draw(Dtext);
	for (int i = 0; i < 6; i++) {
		window->draw(key[i]);
		window->draw(keyText[i]);
	}
}

