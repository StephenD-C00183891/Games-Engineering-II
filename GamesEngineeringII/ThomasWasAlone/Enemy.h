#pragma once
#pragma once
#pragma once

#include "GameObject.h"
#include "BasicTypes.h"
#include "EventListener.h"
#include "Tile.h"

#include <vector>

class Enemy :public GameObject, public EventListener
{

public:
	Enemy(Rect r, int row, int col) :rect(r), row(row), column(col) { };
	Enemy();
	~Enemy();

	std::vector<Tile*> path;

	Rect rect;
	Colour col;
	int row;
	int column;
	int timer;
	int pathCount;


	void Render(Renderer & r);

	void Update(unsigned int deltaTime);

	void onEvent(EventListener::Event);

	void setPos(Tile* pathTile);
	void MoveLeft(Size2D winSize);
	void MoveRight(Size2D winSize);
	void MoveUp(Size2D winSize);
	void MoveDown(Size2D winSize);
};