#include "Map.h"

Map::Map()
{
}

Map::~Map()
{
}

void Map::init()
{

	for (int i = 0; i < A; i++) {
		for (int j = 0; j < A; j++) {
			//Initialise tile map 2
			tile1[i][j].setSize(sf::Vector2f(tileSize, tileSize));
			tile1[i][j].setOutlineThickness(1);
			tile1[i][j].setFillColor(sf::Color(192, 192, 192));
			tile1[i][j].setOutlineColor(sf::Color::Black);
			tile1[i][j].setPosition(sf::Vector2f(-560 + (tileSize * j), -390 + (tileSize * i)));

			//Initialise tile map 2
			tile2[i][j].setSize(sf::Vector2f(tileSize, tileSize));
			tile2[i][j].setOutlineThickness(1);
			tile2[i][j].setFillColor(sf::Color(192, 192, 192));
			tile2[i][j].setOutlineColor(sf::Color::Black);
			tile2[i][j].setPosition(sf::Vector2f(110 + (tileSize * j), -390 + (tileSize * i)));
		}
	}
}

/**Colors blocked tiles on map*/
void Map::setBlocked(ProgramState obst)
{
	switch (obst) {

	case ProgramState::NONE:
		break;
		//Draw the small obstacle on grid
	case ProgramState::SMALL:
		for (int i = 6; i < 12; i++) {
			tile1[5][i].setFillColor(sf::Color::Black);
			tile2[5][i].setFillColor(sf::Color::Black);
		}
		break;
		//Draw the large obstacle on grid
	case ProgramState::LARGE:
		for (int i = 1; i < A; i++) {
			tile1[1][i].setFillColor(sf::Color::Black);
			tile2[1][i].setFillColor(sf::Color::Black);
		}
		break;
		//Draw the surrounding obstacle on grid
	case ProgramState::SURROUNDING:
		for (int i = 2; i < A - 2; i++) {
			for (int j = 2; j < A - 2; j++) {
				if (i == 2) {
					tile1[i][j].setFillColor(sf::Color::Black);
					tile2[i][j].setFillColor(sf::Color::Black);
				}
				else if (j == 2 || j == A - 3) {
					tile1[i][j].setFillColor(sf::Color::Black);
					tile2[i][j].setFillColor(sf::Color::Black);
				}
			}
		}
		break;
		//Draw the even obstacle on grid
	case ProgramState::EVEN:
		for (int i = 5; i < 9; i += 2) {
			for (int j = 0; j < A; j++) {
				tile1[i][j].setFillColor(sf::Color::Black);
				tile2[i][j].setFillColor(sf::Color::Black);
			}
		}
		break;
	default:
		break;
	}
}

/**Updates map grid size*/
void Map::setArraySize(int x, float size)
{
	tileSize = size;
	A = x;

	tile1.clear();
	tile2.clear();

	tile1.resize(x, std::vector<RectangleShape>(x));
	tile2.resize(x, std::vector<RectangleShape>(x));
}

/**Updates map*/
void Map::updateMap(int x, int y, char id, sf::Color c)
{
	//Updates A* map
	if (id == 'a') {
		tile1[x][y].setFillColor(c);
	}
	//Updates Dijkstra map
	if (id == 'd') {
		tile2[x][y].setFillColor(c);
	}
}

/**Resets map tile colors*/
void Map::resetMap()
{
	//Loops through map and resets colors
	for (int i = 0; i < A; i++) {
		for (int j = 0; j < A; j++) {
			tile1[i][j].setFillColor(sf::Color(192, 192, 192));
			tile1[i][j].setSize(sf::Vector2f(tileSize, tileSize));
			tile1[i][j].setPosition(sf::Vector2f(-560 + (tileSize * j), -390 + (tileSize * i)));

			tile2[i][j].setFillColor(sf::Color(192, 192, 192));
			tile2[i][j].setSize(sf::Vector2f(tileSize, tileSize));
			tile2[i][j].setPosition(sf::Vector2f(110 + (tileSize * j), -390 + (tileSize * i)));
		}
	}
}

/**Renders map to window*/
void Map::render(sf::RenderWindow * window)
{
	//Draws tile map
	for (int i = 0; i < A; i++) {
		for (int j = 0; j < A; j++) {
			window->draw(tile1[i][j]);
			window->draw(tile2[i][j]);
		}
	}
}
