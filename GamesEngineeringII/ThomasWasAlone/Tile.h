#pragma once

#include "GameObject.h"
#include "BasicTypes.h"
#include "EventListener.h"

class Tile:public GameObject, public EventListener
{
	
public:
	Tile(Rect r) :rect(r) { };
	Tile();
	~Tile();

	Rect rect;
	Colour col;

	void Render(Renderer & r);

	void Update(unsigned int deltaTime);

	void onEvent(EventListener::Event);
};

