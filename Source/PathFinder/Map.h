#include "StaticSprite.h"
#include "ProgramState.h"
#include <vector>

class Map :
	public StaticSprite {
public: Map();
		~Map();
		void init();
		void setBlocked(ProgramState obst);
		void setArraySize(int x, float size);
		void updateMap(int x, int y, char id, sf::Color c);
		void resetMap();
		void render(sf::RenderWindow* window);

protected:

	//Tile map variables
	int A;
	float tileSize;
	std::vector<std::vector<RectangleShape> > tile1, tile2;
	
};

