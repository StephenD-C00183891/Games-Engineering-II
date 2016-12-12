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

void astar::setCurrent()
{

}

int astar::sortByFcost(std::vector<Tile*> openList)
{
	lowest = openList[0];

	for (int i = 1; i < openList.size(); i++)
	{
		if (openList[i]->_f < lowest->_f)
		{
			lowest = openList[i];
		}
	}

	return 0;
}

void astar::Path(int startRow, int startCol, Tile* goal, std::vector<std::vector<Tile*>>& _tiles, int lineSize)
{

	for (int i = 0; i < lineSize; i++)
	{
		for (int k = 0; k < lineSize; k++)
		{
			_tiles[i][k]->_g = 99999;
			_tiles[i][k]->_h = 99999;
		}
	}

	//Calculate h cost from every tile to goal
	for (int i = 0; i < lineSize; i++)
	{
		for (int k = 0; k < lineSize; k++)
		{
			int x = _tiles[i][k]->GetPosition().x;
			int y = _tiles[i][k]->GetPosition().y;

			float dist = sqrt(((goal->_row - i)*(goal->_row - i)) + ((goal->_column - k)*(goal->_column - k)));
			_tiles[i][k]->_h = dist;
		}
	}

	//openList.push_back(_tiles[startRow][startCol]);
	_tiles[startRow][startCol]->_g = 0;
	path.push_back(_tiles[startRow][startCol]);

	currentRow = startRow;
	currentCol = startCol;
	openList.push_back(_tiles[currentRow][currentCol]);


	while (_tiles[currentRow][currentCol] != goal)
	{
		fillList(currentRow, currentCol, _tiles, lineSize);
				
		//openList.push_back(adjacentList);
		closedList.push_back(openList.at(0));
		openList.erase(openList.begin());
		for (int l = 0; l < openList.size(); l++)
		{
			calculateFCost(openList[l], _tiles[currentRow][currentCol]);
		}
		sortByFcost(openList);

		path.push_back(lowest);
		currentRow = lowest->_row;
		currentCol = lowest->_column;
		lowest->setMarked(true);
		
	}
}

//void astar::FindPath(Tile* start, Tile* goal, std::vector<std::vector<Tile*>>& _tiles, int lineSize)
//{
//
//	
//	for (int i = 0; i < lineSize; i++)
//	{
//		for (int k = 0; k < lineSize; k++)
//		{
//			_tiles[i][k]->_g = 99999;
//			_tiles[i][k]->_h = 99999;
//		}
//	}
//
//	start->_g = 0;
//	if (pq.top() == start)
//	{
//		pq.top()->prev = NULL;
//	}
//
//	pq.push(start);
//	start->setMarked(true);
//	pq.top()->SetPrevious(NULL);
//
//	int gX = goal->GetPosition().x;
//	int gY = goal->GetPosition().y;
//
//	//Calculate h cost from every tile to goal
//	for (int i = 0; i < lineSize; i++)
//	{
//		for (int k = 0; k < lineSize; k++)
//		{
//			int x = _tiles[i][k]->GetPosition().x;
//			int y = _tiles[i][k]->GetPosition().y;
//
//			float dist = sqrt(((gX - x)*(gX - x)) + ((gY - y)*(gY - y)));
//			_tiles[i][k]->_h = dist;
//		}
//	}
//
//	
//
//
//	//check if the size is not 0 and if the top of the priority queue is not the destination
//	while (pq.size() != 0 && pq.top() != goal)
//	{
//		
//			if ( pq.top() != pq.top()->GetPrevious())
//			{
//				//calculate h cost and g cost 
//				int hN = pq.top()->_h;
//				int gN = pq.top()->_g + 1;
//				int distC = gN + hN;
//				
//
//				int fC = pq.top()->_g + pq.top()->_h;
//				//check if the distance is less than the f cost
//				if (distC < fC) {
//
//					pq.top()->SetPrevious(pq.top());
//					pq.top()->_g = gN;
//					pq.top()->_h = hN;
//					pq.pop();
//					//(*iter).node()->setData(NodeType(get<0>((*iter).node()->data()), gN, hN/*get<2>((*iter).node()->data())*/, get<3>((*iter).node()->data()), get<4>((*iter).node()->data())));
//				}
//			}
//		}
//	
//}

void astar::fillList(int startRow, int startCol, std::vector<std::vector<Tile*>>& _tiles, int lineSize)
{
	openList.clear();

	if (startRow >= 1)
	{
		openList.push_back(_tiles[startRow - 1][startCol]);
	}
	if (startCol >= 1)
	{
		openList.push_back(_tiles[startRow][startCol - 1]);
	}
	if (startCol < lineSize)
	{
		openList.push_back(_tiles[startRow][startCol + 1]);
	}
	if (startRow < lineSize)
	{
		openList.push_back(_tiles[startRow + 1][startCol]);
	}
}

float astar::calculateFCost(Tile* n1, Tile* n2)
{
	n1->_f = n1->_g + n1->_h;
	n2->_f = n2->_g + n2->_h;

	return n1->_f > n2->_f;
}

void astar::Update(unsigned int deltaTime) {


}

void astar::onEvent(EventListener::Event evt)
{

}

