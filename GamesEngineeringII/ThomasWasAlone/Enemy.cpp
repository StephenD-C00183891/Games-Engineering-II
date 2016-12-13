#include "stdafx.h"

#include "Enemy.h"


Enemy::Enemy()
{
}

Enemy::~Enemy()
{
}

void Enemy::Render(Renderer& r) {
	r.drawWorldRect(rect, col);
}


void Enemy::Update(unsigned int deltaTime) {

	timer += 1;

	if (timer > 5)
	{
		if (pathCount < path.size())
		{
			setPos(path[pathCount]);
			timer = 0;
			pathCount++;
		}
	}
}

void Enemy::onEvent(EventListener::Event evt)
{
	
}

void Enemy::setPos(Tile* pathTile)
{
	rect.pos.x = (pathTile->_column * rect.size.w);
	rect.pos.y = (pathTile->_row * rect.size.h);
}

void Enemy::MoveLeft(Size2D winSize)
{
	if (rect.pos.x >= 0)
	{
		rect.pos.x -= rect.size.w;
	}
}

void Enemy::MoveRight(Size2D winSize)
{
	if (rect.pos.x <= (winSize.w - (rect.size.w * 2)))
	{
		rect.pos.x += rect.size.w;
	}
}

void Enemy::MoveUp(Size2D winSize)
{
	if (rect.pos.y >= 0)
	{
		rect.pos.y += rect.size.h;
	}
}

void Enemy::MoveDown(Size2D winSize)
{
	if (rect.pos.y <= (winSize.h - rect.size.h))
	{
		rect.pos.y -= rect.size.h;
	}
}
