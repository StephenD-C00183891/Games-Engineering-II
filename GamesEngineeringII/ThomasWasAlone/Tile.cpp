#include "stdafx.h"

#include "Tile.h"


Tile::Tile(Rect r, Type t, bool full, int f, int g, int h, int row, int column)
	: _rect(r)
	, _type(t)
	, _full(full)
	, _f(f)
	, _g(g)
	, _h(h)
	, _row(row)
	, _column(column)
{
	switch (_type)
	{//set the colour based on its type
	case Type::Wall:
		_col = Colour(0, 0, 0, 255);
		break;
	case Type::Walkable:
		_col = Colour(255, 255, 255, 255);
		break;
	}
}

Tile::~Tile()
{
}

void Tile::Render(Renderer& r) {
	r.drawWorldRect(_rect, _col);
}


void Tile::Update(unsigned int deltaTime)
{
	if (marked == true)
	{
		_col = Colour(200, 0, 0, 255);
	}
	else
	{
		_col = Colour(255, 255, 255, 255);
	}

}

void Tile::onEvent(EventListener::Event evt)
{

}

void Tile::setMarked(bool mark)
{
	marked = mark;
}

Rect Tile::GetRect()
{
	return _rect;
}

void Tile::SetPrevious(Tile* _tile)
{
	prev = _tile;
}

Tile * Tile::GetPrevious()
{
	return prev;
}

Tile * Tile::GetTile()
{
	Tile *thisTile = this;
	return thisTile;
}

Point2D Tile::GetPosition()
{
	Point2D pos = _rect.pos;

	return pos;
}
