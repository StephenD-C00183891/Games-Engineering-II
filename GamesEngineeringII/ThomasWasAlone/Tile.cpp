#include "stdafx.h"

#include "Tile.h"


Tile::Tile(Rect r, Type t)
	: _rect(r)
	, _type(t)
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


void Tile::Update(unsigned int deltaTime) {


}

void Tile::onEvent(EventListener::Event evt)
{

}

Rect Tile::GetRect()
{
	return _rect;
}


Point2D Tile::GetPosition()
{
	Point2D pos = _rect.pos;

	return pos;
}
