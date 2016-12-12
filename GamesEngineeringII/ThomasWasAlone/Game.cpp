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
	i = 0;
	//creates our renderer, which looks after drawing and the window
	renderer.init(winSize,"A* Project");

	//set up the viewport
	//we want the vp centred on origin and 20 units wide
	float aspectRatio = winSize.w / winSize.h;
	float vpWidth = 20;
	Size2D vpSize(vpWidth, vpWidth /aspectRatio);
	Point2D vpBottomLeft( -vpSize.w / 2, - vpSize.h / 2);

	Rect vpRect(vpBottomLeft,vpSize);
	renderer.setViewPort(vpRect);

	lineSize = 30;
	MAXTILES = (lineSize * lineSize);
	wallSpawn = 12;
	enemyCount = 5;

	line = 0;
	column = 0;
	lineSize = sqrt(MAXTILES);

	tileWidth = winSize.w / lineSize;
	tileHeight = winSize.h / lineSize;


	for (int i = 0; i < lineSize; i++)
	{
		std::vector<Tile*> temp_vect;

		for (int k = 0; k < lineSize; k++)
		{
			Tile* tile = new Tile(Rect(0 + (tileWidth*line), 0 + (tileHeight*column), tileWidth, tileHeight), Tile::Type::Walkable, false, 0, 0, 0, i, k);
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
	cout << "Tiles Loaded" << endl;

	p1 = new Player(Rect(tiles[0][0]->GetPosition().x, tiles[0][0]->GetPosition().y, tileWidth, tileHeight));
	tiles[0][0]->_full = true;
	p1->col = Colour(255, 0, 0);

	for (int i = 0; i < enemyCount; i++)
	{
		int randX = rand() % (lineSize - 1);
		int randY = rand() % (lineSize - 1);

		if (tiles[randX][randY]->_full == false)
		{
			Enemy* en = new Enemy(Rect(tiles[randX][randY]->GetPosition().x, tiles[randX][randY]->GetPosition().y, tileWidth, tileHeight), randX, randY);
			enemies.push_back(en);
			enemies[i]->col = Colour(0, 255, 0);
			tiles[randX][randY]->_full = true;
		}
		else if (tiles[randX][randY]->_full == true)
		{
			i--;
		}
	}

	for (int i = 0; i < enemyCount; i++)
	{
		enemyPath = star.Path(28, 28, tiles[0][0], tiles, lineSize);
	}

	inputManager.AddListener(EventListener::Event::LEFT, this);
	inputManager.AddListener(EventListener::Event::RIGHT, this);
	inputManager.AddListener(EventListener::Event::UP, p1);
	inputManager.AddListener(EventListener::Event::DOWN, p1);

	lastTime = LTimer::gameTime();

	inputManager.AddListener(EventListener::Event::PAUSE, this);
	inputManager.AddListener(EventListener::Event::QUIT, this);

	//star.Path(0, 10, tiles[15][6], tiles, lineSize);

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

	for (int i = 0; i < enemies.size(); i++)
	{
		delete enemies[i];
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
	for (int i = 0; i < enemies.size(); i++)
	{
		enemies[i]->Update(deltaTime);
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

	for (int i = 0; i < enemies.size(); i++)
	{
		enemies[i]->Render(renderer);
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
}
