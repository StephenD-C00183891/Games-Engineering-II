#pragma once
#pragma once

#include <vector>
#include <list>
#include <queue>

#include "GameObject.h"
#include "BasicTypes.h"
#include "EventListener.h"
#include "Tile.h"

class astar
{

public:


	
	astar();
	~astar();

	std::vector<Tile*> openList;
	std::vector<Tile*> closedList;
	std::vector<Tile*> adjacentList;
	std::vector<Tile*> path;

	Tile* lowest;

	void Render(Renderer & r);

	void fillList(int startRow, int startCol, std::vector<std::vector<Tile*>>& _tiles, int lineSize);

	float calculateFCost(Tile* n1, Tile* n2);

	int currentRow;
	int currentCol;

	void Update(unsigned int deltaTime);
	void setCurrent();
	int sortByFcost(std::vector<Tile*> openLIst);

	void Path(int startRow, int startCol, Tile * goal, std::vector<std::vector<Tile*>>& _tiles, int lineSize);

	//void FindPath(Tile* start, Tile* goal, std::vector<std::vector<Tile*>>& tiles, int lineSize);

	void onEvent(EventListener::Event);
	
	class NodeSearchCostComparer {
	public:
		bool operator()(Tile * n1, Tile * n2) {

			return n1->_g + n1->_h > n2->_g + n2->_h;
		}
	};

	std::priority_queue<Tile *, std::vector<Tile*>, NodeSearchCostComparer> pq;
};

