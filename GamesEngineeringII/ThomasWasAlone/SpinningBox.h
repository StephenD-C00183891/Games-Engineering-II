#pragma once

#include "GameObject.h"
#include "BasicTypes.h"
#include "EventListener.h"

/**define a box that spins aronf the centre*/
class SpinningBox:public GameObject, public EventListener
{
	
public:
	SpinningBox(Rect r) :rect(r) { angVel = .0f; };
	SpinningBox();
	~SpinningBox();

	Rect rect;
	Colour col;

	float angVel; //control rate of spin

	void Render(Renderer & r);

	void Update(unsigned int deltaTime);

	void onEvent(EventListener::Event);
};

