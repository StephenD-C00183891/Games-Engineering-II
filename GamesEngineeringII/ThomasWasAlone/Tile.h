#pragma once

#include "GameObject.h"
#include "BasicTypes.h"
#include "EventListener.h"

class Tile:public GameObject, public EventListener
{
	
public:

	enum class Type
	{
		Wall,
		Walkable
	};

	Tile(Rect r, Type t) ;
	Tile();
	~Tile();

	Rect _rect;
	Type _type;
	Colour _col;

	void Render(Renderer & r);

	void Update(unsigned int deltaTime);

	void onEvent(EventListener::Event);
};

