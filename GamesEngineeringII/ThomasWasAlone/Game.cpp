#include "stdafx.h"

#include <iostream>
using namespace std;



#include "LTimer.h"
//#include "Tile.h"
#include "Game.h"


const int SCREEN_FPS = 100;
const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;


Game::Game()
{
	pause = false;
	quit = false;
}


Game::~Game()
{
}


bool Game::init() {	
	Size2D winSize(800,600);

	wS.h = winSize.h;
	wS.w = winSize.w;

	//creates our renderer, which looks after drawing and the window
	renderer.init(winSize,"Simple SDL App");

	//set up the viewport
	//we want the vp centred on origin and 20 units wide
	float aspectRatio = winSize.w / winSize.h;
	float vpWidth = 20;
	Size2D vpSize(vpWidth, vpWidth /aspectRatio);
	Point2D vpBottomLeft( -vpSize.w / 2, - vpSize.h / 2);

	Rect vpRect(vpBottomLeft,vpSize);
	renderer.setViewPort(vpRect);

	lineSize = 20;
	MAXTILES = (lineSize * lineSize);
	wallSpawn = 12;
	spawnCount = 0;
	yPos = 0;
	

	line = 0;
	column = 0;
	lineSize = sqrt(MAXTILES);

	tileWidth = winSize.w / lineSize;
	tileHeight = winSize.h / lineSize;


	for (int i = 0; i < MAXTILES; i++)
	{
		std::vector<Tile*> temp_vect;

		for (int i = 0; i < lineSize; i++)
		{
			Tile* tile = new Tile(Rect(0 + (tileWidth*line), 0 + (tileHeight*column), tileWidth, tileHeight), Tile::Type::Walkable);
			line += 1;
			temp_vect.push_back(tile);
		}

		if (line >= lineSize)
		{
			column += 1;
			line = 0;
			tiles.push_back(temp_vect);
		}
	}
		/*Tile* tile = new Tile(Rect(0 + (tileWidth*line), 0 + (tileHeight*column), tileWidth, tileHeight), Tile::Type::Walkable);
		gameObjects.push_back(tile);
		line += 1;
		spawnCount += 1;

		if(line >= lineSize)
		{
			column += 1;
			line = 0;
		}*/
	//}

	p1 = new Player(Rect(0, 0, tileWidth, tileHeight));
	p1->col = Colour(255, 0, 0);

	inputManager.AddListener(EventListener::Event::LEFT, this);
	inputManager.AddListener(EventListener::Event::RIGHT, this);
	inputManager.AddListener(EventListener::Event::UP, p1);
	inputManager.AddListener(EventListener::Event::DOWN, p1);

	lastTime = LTimer::gameTime();

	inputManager.AddListener(EventListener::Event::PAUSE, this);
	inputManager.AddListener(EventListener::Event::QUIT, this);

	return true;
}


void Game::destroy()
{
	vector< vector<Tile*> >::iterator row;
	vector<Tile*>::iterator col;

	for (row = tiles.begin(); row != tiles.end(); row++)
	{
		for(col = row->begin(); col != row->end(); col++)
		{
			delete *col;
		}
	}

	tiles.clear();
	renderer.destroy();
}

void Game::update()
{
	unsigned int currentTime = LTimer::gameTime();//millis since game started
	unsigned int deltaTime = currentTime - lastTime;//time since last update

	vector< vector<Tile*> >::iterator row;
	vector<Tile*>::iterator col;

	for (row = tiles.begin(); row != tiles.end(); row++)
	{
		for (col = row->begin(); col != row->end(); col++)
		{
			(*col)->Update(deltaTime);
		}
	}


	lastTime = currentTime;
}

void Game::render()
{
	renderer.clear(Colour(0,0,0));

	vector< vector<Tile*> >::iterator row;
	vector<Tile*>::iterator col;

	for (row = tiles.begin(); row != tiles.end(); row++)
	{
		for (col = row->begin(); col != row->end(); col++)
		{
			(*col)->Render(renderer);
		}
	}

	p1->Render(renderer);

	renderer.present();
}

void Game::loop()
{
	LTimer capTimer;

	int frameNum = 0;
	while (!quit) { 
		capTimer.start();

		inputManager.ProcessInput();

		if(!pause) 
			update();
		render();

		int frameTicks = capTimer.getTicks();
		if (frameTicks < SCREEN_TICKS_PER_FRAME)
		{
			SDL_Delay(SCREEN_TICKS_PER_FRAME - frameTicks);
		}
	}
}

void Game::onEvent(EventListener::Event evt) {

	if (evt == EventListener::Event::PAUSE) {
		pause = !pause;
	}
	
	if (evt == EventListener::Event::QUIT) {
		quit=true;
	}

	if (evt == EventListener::Event::LEFT)
	{
		p1->MoveLeft(wS);
	}
	if (evt == EventListener::Event::RIGHT)
	{
		p1->MoveRight(wS);
	}
	if (evt == EventListener::Event::UP)
	{
		p1->MoveUp(wS);
	}
	if (evt == EventListener::Event::DOWN)
	{
		p1->MoveDown(wS);
	}
}
