#include "stdafx.h"

#include "astar.h"


astar::astar()
{

}

astar::~astar()
{
}

void astar::Render(Renderer& r) {

}

void astar::sortByFcost(std::vector<Tile*> openList)
{

	for (int i = 0; i < openList.size(); i++)
	{
		if (openList[i]->_f <= lowest->_f)
		{
			lowest = openList[i];
		}
	}
}

std::vector<Tile*> astar::Path(int startRow, int startCol, Tile* goal, std::vector<std::vector<Tile*>>& _tiles, int lineSize)
{

	//Calculate h cost from every tile to goal
	for (int i = 0; i < lineSize; i++)
	{
		for (int k = 0; k < lineSize; k++)
		{
			float dist = sqrt(((goal->_row - i)*(goal->_row - i)) + ((goal->_column - k)*(goal->_column - k)));
			_tiles[i][k]->_h = dist;
		}
	}

	_tiles[startRow][startCol]->_g = 0;

	lowest = _tiles[startRow][startCol];
	lowest->setMarked(true);
	path.push_back(_tiles[startRow][startCol]);
	
	currentRow = startRow;
	currentCol = startCol;
	openList.push_back(_tiles[currentRow][currentCol]);

	int prev_g = _tiles[startRow][startCol]->_g;

	while (openList.size() != 0)
	{

		if (_tiles[currentRow][currentCol] != goal)
		{
			openList.clear();
			openList.push_back(_tiles[currentRow][currentCol]);

			closedList.push_back(openList.at(0));

			fillList(currentRow, currentCol, _tiles, lineSize);

			for (int l = 0; l < openList.size(); l++)
			{
				openList[l]->_g = prev_g + 1;
				calculateFCost(openList[l], _tiles[currentRow][currentCol]);
			}

			sortByFcost(openList);

			
			path.push_back(lowest);
			lowest->setMarked(true);
			prev_g = lowest->_g;
			currentRow = lowest->_row;
			currentCol = lowest->_column;

			if (_tiles[currentRow][currentCol] == goal)
			{
				openList.clear();
				return path;
			}
		}
	}
}

void astar::fillList(int startRow, int startCol, std::vector<std::vector<Tile*>>& _tiles, int lineSize)
{
	if (startRow > 0)
	{
	//	if (_tiles[startRow - 1][startCol]->marked == false)
		//{
			openList.push_back(_tiles[startRow - 1][startCol]);
			//_tiles[startRow - 1][startCol]->setMarked(true);
		//}
	}
	if (startCol > 0)
	{
		//if (_tiles[startRow][startCol - 1]->marked == false)
		//{
			openList.push_back(_tiles[startRow][startCol - 1]);
			//_tiles[startRow][startCol - 1]->setMarked(true);
		//}
	}
	if (startCol < lineSize)
	{
		//if (_tiles[startRow][startCol + 1]->marked == false)
		//{
			openList.push_back(_tiles[startRow][startCol + 1]);
			//_tiles[startRow][startCol + 1]->setMarked(true);
		//}
	}
	if (startRow < lineSize)
	{
		//if (_tiles[startRow + 1][startCol]->marked == false)
		//{
			openList.push_back(_tiles[startRow + 1][startCol]);
			//_tiles[startRow + 1][startCol]->setMarked(true);
		//}
	}
}

float astar::calculateFCost(Tile* n1, Tile* n2)
{
	n1->_f = n1->_g + n1->_h;
	n2->_f = n2->_g + n2->_h;

	return n1->_g + n1->_h + n2->_g + n2->_h;
}

void astar::Update(unsigned int deltaTime) {


}

void astar::onEvent(EventListener::Event evt)
{

}

