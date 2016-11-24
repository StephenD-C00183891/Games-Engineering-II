#include "stdafx.h"

#include "Tile.h"


Tile::Tile()
{
}

Tile::~Tile()
{
}

void Tile::Render(Renderer& r) {
	r.drawWorldRect(rect,col);
}


void Tile::Update(unsigned int deltaTime) {


}

void Tile::onEvent(EventListener::Event evt)
{

}
