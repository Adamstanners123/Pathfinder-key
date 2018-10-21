#include "RenderLoop.h"
#include "ProgramState.h"
#include <list>
#include <set>


using namespace std;

struct Coords {

	int x, y;
};

struct Grid {

	Coords coord;
	Coords parent;
	bool blocked = false;
	int gCost = 0, hCost = 0, fCost = 0;
	std::list<Coords> neighbours;
};

/** Custom operator to compare coordinates*/
inline bool operator<(const Coords& lhs, const Coords& rhs)
{
	if (lhs.x < rhs.x) return true;
	else if ((lhs.x == rhs.x) && (lhs.y < rhs.y)) {
		return true;
	}
	else return false;
}

class Astar
{
private:
	
	//Grid used in main algorithim
	int A = 0;
	vector<vector<Grid> > grid;

	//List to be returned to loop class
	list<Coords> l;

public:

/** Resets all grid neighbours and sets blocked to false*/
void resetCoordsAndNeighbours() {
	
	//Loops through each element in array and resets it to its original state
	for (int i = 0; i < A; i++) {
		for (int j = 0; j < A; j++) {

			grid[i][j].neighbours.clear();
			//grid[i][j].blocked = false;
		}
	}
	
}

/** Assigns each tiles neighbours and assigns a default coordinate value*/
void assignCoordsAndNeighbours() {

	
	//Loops through each element in array
	for (int i = 0; i < A; i++) {
		for (int j = 0; j < A; j++) {
			
			grid[i][j].coord = { i, j };

			if (j < A - 1 && grid[i][j + 1].blocked == false) {	//Checks that tile is within map range and is not blocked
				Coords c = { i, j + 1 };
				grid[i][j].neighbours.push_back(c);
			}
			else {												//Assigns default neighbour 
				Coords c = grid[i][j].coord;					
				grid[i][j].neighbours.push_back(c);
			}
			if (i <  A - 1 && grid[i + 1][j].blocked == false) {	//Checks that tile is within map range and is not blocked
				Coords c = { i + 1, j };
				grid[i][j].neighbours.push_back(c);
			}
			else {												//Assigns default neighbour 
				Coords c = grid[i][j].coord;
				grid[i][j].neighbours.push_back(c);
			}
			if (j > 0 && grid[i][j - 1].blocked == false) {		//Checks that tile is within map range and is not blocked
				Coords c = { i, j - 1 };
				grid[i][j].neighbours.push_back(c);
			}
			else {												//Assigns default neighbour 
				Coords c = grid[i][j].coord;
				grid[i][j].neighbours.push_back(c);
			}
			if (i > 0 && grid[i - 1][j].blocked == false) {		//Checks that tile is within map range and is not blocked
				Coords c = { i - 1, j };
				grid[i][j].neighbours.push_back(c);
			}
			else {												//Assigns default neighbour 
				Coords c = grid[i][j].coord;
				grid[i][j].neighbours.push_back(c);
			}
		}
	}
}

/** Finds the tile with the lowest fcost and returns its index*/
Coords minimumFcost(set<Coords> &open)
{
	// Initialize min value and index
	int min = 456789;
	Coords min_index = {};
	std::set<Coords>::iterator it = open.begin();

	//Loop through each open tile and find the one with the lowest fcost
	while (it != open.end())
	{
		Coords node = *it;
		if (grid[node.x][node.y].fCost < min && grid[node.x][node.y].blocked == false) {
			min = grid[node.x][node.y].fCost; min_index = node;
		}
		it++;
	}

	return min_index;
}

/** Manhattan distance heuristic, returns hcost*/
int heuristic(Coords node, Coords goal) {

	//Takes difference between tile position and goal position and returns it
	int dx = abs(node.x - goal.x);
	int dy = abs(node.y - goal.y);

	return (dx + dy);
}

/** Main A* pathfinding algorithim, is given a key to determine what pathfinding is desired
0 = Dijkstra; 1 = A*. Also returns a list containing the shortest path */
list<Coords> aStar(Coords start, Coords goal, int key) {


	//Sets for organising visited and unvisited tiles
	set<Coords> open;
	set<Coords> closed;
	list<Coords> list;
	
	//Clears list for map drawing and assigns neighbours
	l.clear();
	assignCoordsAndNeighbours();

	//Compute f/g/h for the start tile
	grid[start.x][start.y].gCost = 0;
	grid[start.x][start.y].fCost = grid[start.x][start.y].gCost + (heuristic(start, goal) * key);

	//Add start tile to open set
	open.insert(start);

	//Loop until set is empty
	while (!open.empty()) {

		//Pick the most promising node to focus on next
		Coords current = minimumFcost(open);

		//Checks if we have arrived at goal
		if (current.x == goal.x && current.y == goal.y) {
			//End is found - we are finished!
			break;
		}

		//Moves current coord from open to closed
		open.erase(current);
		closed.insert(current);

		//Temp variable for tiles neighbours
		list = grid[current.x][current.y].neighbours;

		//Loops for each neighbour
		for (int i = 0; i < 4; i++) {
			//Checks that tile is not blocked
			if (grid[current.x][current.y].blocked == false) {
				
				Coords adj = list.back();
				list.pop_back();

				if (closed.count(adj)) { //Already finished with this node
					continue;
				}
				//Set new gcost
				int new_gCost = grid[current.x][current.y].gCost + 1;
				//Adds tile to open set
				if (!open.count(adj)) {
					open.insert(adj);
					l.push_back(adj);
				}
				else if (new_gCost >= grid[adj.x][adj.y].gCost) {
					//Seen this tile before and already found a shorter path to it from the start
					continue;
				}
				//Compute f/g/h for current tile
				grid[adj.x][adj.y].gCost = new_gCost;
				grid[adj.x][adj.y].fCost = grid[adj.x][adj.y].gCost + (heuristic(adj, goal) * key);
				grid[adj.x][adj.y].parent = current;
			}
		}
	}

	//List to contain path
	std::list<Coords> path;
	Coords node = goal;

	//Traces its way back from goal to start
	while (node.x != start.x || node.y != start.y) {
		path.push_back(node);
		node = grid[node.x][node.y].parent;
	}

	//Adds start to path and reverses both the drawing and path lists
	path.push_back(start);
	std::reverse(path.begin(), path.end());
	std::reverse(l.begin(), l.end());

	return path;
}

/** Returns a list of visited tiles for use in map drawing*/
list<Coords> getList() {

	return l;
}

/** Updates pathfinding grid size*/
void setArraySize(int x) {

	A = x;
	grid.clear();
	grid.resize(x, vector<Grid> (x));

}
/** Is given the obstacle type and uses this to set the required 
	tiles to blocked*/
void setBlocked(ProgramState obst) {

	switch (obst) {
		//If no obstacle do nothing
	case ProgramState::NONE:
		break;
		//If small obstacle selected set tiles to blocked
	case ProgramState::SMALL:
		for (int i = 6; i < 12; i++) {
			grid[5][i].blocked = true;
		}
		break;
		//If large obstacle selected set tiles to blocked
	case ProgramState::LARGE:
		for (int i = 1; i < A; i++) {
			grid[1][i].blocked = true;
		}
		break;
		//If surrounding obstacle selected set tiles to blocked
	case ProgramState::SURROUNDING:
		for (int i = 2; i < (A - 2); i++) {
			for (int j = 2; j < (A - 2); j++) {
				if (i == 2) {
					grid[i][j].blocked = true;
				}
				else if (j == 2 || j == A - 3) {
					grid[i][j].blocked = true;
				}
			}
		}
		break;
		//If even obstacle selected set tiles to blocked
	case ProgramState::EVEN:
		for (int i = 5; i < 9; i += 2) {
			for (int j = 0; j < A; j++) {
				grid[i][j].blocked = true;
			}
		}
		break;
		//Default
	default:
		break;
	}
}

};