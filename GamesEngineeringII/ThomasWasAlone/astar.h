#pragma once
#pragma once

#include <vector>>

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


	void Render(Renderer & r);

	void Update(unsigned int deltaTime);

	void onEvent(EventListener::Event);
};

