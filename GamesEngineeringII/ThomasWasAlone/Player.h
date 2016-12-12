#pragma once

#include "GameObject.h"
#include "BasicTypes.h"
#include "EventListener.h"
#include <vector>

class Player :public GameObject, public EventListener
{

public:
	Player(Rect r) :rect(r) { };
	Player();
	~Player();

	Rect rect;
	Colour col;


	void Render(Renderer & r);

	void Update(unsigned int deltaTime);

	void onEvent(EventListener::Event);

	void MoveLeft(Size2D winSize);
	void MoveRight(Size2D winSize);
	void MoveUp(Size2D winSize);
	void MoveDown(Size2D winSize);
};