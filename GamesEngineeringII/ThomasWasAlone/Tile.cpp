#include "stdafx.h"

#include "Tile.h"


Tile::Tile(Rect r, bool marked, bool full, int f, int g, int h, int row, int column)
	: _rect(r)
	, marked(marked)
	, _full(full)
	, _f(f)
	, _g(g)
	, _h(h)
	, _row(row)
	, _column(column)
{

}


Tile::~Tile()
{

}

void Tile::Render(Renderer& r) {


	r.drawWorldRect(_rect, _col);
}

void Tile::Render2(Renderer& r, int offsetX, int offsetY) {

	r.drawWorldRect(Rect(_rect.pos.x - offsetX, _rect.pos.y - offsetY, _rect.size.w, _rect.size.h), _col);
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
