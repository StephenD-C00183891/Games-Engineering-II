#include "stdafx.h"

#include "Player.h"


Player::Player()
{
}

Player::~Player()
{
}

void Player::Render(Renderer& r) {
	r.drawWorldRect(rect, col);
}


void Player::Update(unsigned int deltaTime) {


}

void Player::onEvent(EventListener::Event evt)
{

}

void Player::MoveLeft(Size2D winSize)
{
	if (rect.pos.x >= 0)
	{
		rect.pos.x -= rect.size.w;
	}
}

void Player::MoveRight(Size2D winSize)
{
	if (rect.pos.x <= (winSize.w - (rect.size.w*2)))
	{
		rect.pos.x += rect.size.w;
	}
}

void Player::MoveUp(Size2D winSize)
{
	if (rect.pos.y >= 0 )
	{
		rect.pos.y += rect.size.h;
	}
}

void Player::MoveDown(Size2D winSize)
{
	if (rect.pos.y <= (winSize.h - rect.size.h))
	{
		rect.pos.y -= rect.size.h;
	}
}
