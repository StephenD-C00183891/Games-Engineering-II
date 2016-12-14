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
	std::vector<Tile*> fullPath;


	std::vector<Tile*>::iterator it;

	Tile* lowest;
	Tile* start_low;
	void Render(Renderer & r);

	void fillList(int startRow, int startCol, std::vector<std::vector<Tile*>>& _tiles, int lineSize);

	float calculateFCost(Tile* n1, Tile* n2);

	int currentRow;
	int currentCol;

	void Update(unsigned int deltaTime);
	void sortByFcost(std::vector<Tile*> openLIst);

	std::vector<Tile*> Path(int startRow, int startCol, std::vector<Tile*> waypoints, std::vector<std::vector<Tile*>>& _tiles, int lineSize);

	void onEvent(EventListener::Event);
};

