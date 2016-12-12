#pragma once

#include "GameObject.h"
#include "BasicTypes.h"
#include "EventListener.h"

class Tile:public GameObject, public EventListener
{
	
public:

	enum class Type : Uint8
	{
		Wall,
		Walkable
	};

	Tile(Rect r, Type t, bool full, int f, int g, int h, int row, int col) ;
	Tile();
	~Tile();

	Rect _rect;
	Type _type;
	Colour _col;
	bool _full;
	int _f;
	int _g;
	int _h;
	int _row;
	int _column;

	//int row;
	//int column;

	bool marked;
	Tile * prev;

	void Render(Renderer & r);

	void Update(unsigned int deltaTime);

	void onEvent(EventListener::Event);

	void setMarked(bool mark);

	Rect GetRect();

	void SetPrevious(Tile *_tile);

	Tile * GetPrevious();

	Tile * GetTile();

	Point2D GetPosition();


};

