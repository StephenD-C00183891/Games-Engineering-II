#include "stdafx.h"

#include <iostream>

using namespace std;



#include "LTimer.h"
//#include "Tile.h"
#include "Game.h"


const int SCREEN_FPS = 100;
const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;


struct ThreadData
{
	int index = -1;
	int _row;
	int _col;
	Tile* goal;
};

SDL_mutex* threadLock = SDL_CreateMutex();
std::queue<ThreadData> jobQueue;
std::vector<std::vector<Tile*>> tiles;
std::vector <Enemy*> enemies;
std::vector<Tile*> waypoints;
astar star;
int lineSize;

bool compare(Tile* i, Tile* j) {
	int i2 = i->_column;
	int j2 = j->_column;
	return (i2>j2);
}

int Game::threaded(void *data)
{
	while (true)
	{
		if (jobQueue.size() != 0) {};

		SDL_LockMutex(threadLock);
		ThreadData tData;
		if (jobQueue.size() > 0)
		{
			tData = jobQueue.front();
			jobQueue.pop();
		}

		SDL_UnlockMutex(threadLock);

		if (tData.index != -1)
		{
			//enemies[i]->path = star.Path(enemies[i]->row, enemies[i]->column, waypoints[j], tiles, lineSize);
			enemies[tData.index]->path = star.Path(tData._row, tData._col, waypoints, tiles, lineSize);
		}
	}

	return 0;
}

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
	//threadLock = SDL_CreateMutex();

	wS.h = winSize.h;
	wS.w = winSize.w;
	cameraRow = 0;
	cameraCol = 0;
	//creates our renderer, which looks after drawing and the window
	renderer.init(winSize,"A* Project");

	//camera=(Rect((tileWidth*cameraCol), (tileHeight*cameraRow), 800, 600));

	//set up the viewport
	//we want the vp centred on origin and 20 units wide
	float aspectRatio = winSize.w / winSize.h;
	float vpWidth = 10;
	Size2D vpSize(vpWidth, vpWidth /aspectRatio);
	Point2D vpBottomLeft( -vpSize.w / 2, - vpSize.h / 2);

	Rect vpRect(vpBottomLeft,vpSize);
	renderer.setViewPort(vpRect);

	lineSize = 50;
	MAXTILES = (lineSize * lineSize);
	wallSpawn = 12;
	enemyCount = 2;

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

			if (k == (lineSize / 4) && i <(lineSize/4)* 3 || k == (lineSize / 4) * 2 && i > (lineSize / 4) || k == (lineSize / 4) * 3 && i <(lineSize / 4) * 3)
			{
				Tile* tile = new Tile(Rect(0 + (tileWidth*line), 0 + (tileHeight*column), tileWidth, tileHeight), true, false, 0, 0, 0, i, k);
				line += 1;
				temp_vect.push_back(tile);
			}
			else
			{
				Tile* tile = new Tile(Rect(0 + (tileWidth*line), 0 + (tileHeight*column), tileWidth, tileHeight), false, false, 0, 0, 0, i, k);
				line += 1;
				temp_vect.push_back(tile);
			}
		}

		if (line >= lineSize)
		{
			column += 1;
			line = 0;
			tiles.push_back(temp_vect);
		}
	}

	p1 = new Player(Rect(tiles[0][0]->GetPosition().x, tiles[0][0]->GetPosition().y, tileWidth, tileHeight));
	tiles[0][0]->_full = true;
	//tiles[1][0]->marked == true;
	p1->col = Colour(255, 0, 0);
	waypoints.push_back(tiles[0][0]);

	for (int row = 0; row < lineSize; row++)
	{
		for (int col = 0; col < lineSize; col++)
		{
			if (row > 0)
			{
				if (tiles[row - 1][col]->marked == true)
				{
					if (tiles[row][col]->marked == false)
					{
						waypoints.push_back(tiles[row][col]);
					}
				}
			}
			if (row < lineSize - 1)
			{
				if (tiles[row + 1][col]->marked == true)
				{
					if (tiles[row][col]->marked == false)
					{
						waypoints.push_back(tiles[row][col]);
					}
				}
			}
		}
	}

	cout << "Tiles Loaded" << endl;

	for (int i = 0; i < enemyCount; i++)
	{
		int randX = rand() % (lineSize - 1);
		//int randY = rand() % (lineSize - 1) + (lineSize/4);
		int randY = lineSize - 5;

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

	std::sort(waypoints.begin(), waypoints.end(), compare);

	for (int i = 0; i < enemies.size(); i++)
	{
		//for (int j = 0; j < waypoints.size(); j++)
		//{
		
		//	if (j == 0)
		//	{
				jobCreation(i, enemies[i]->row, enemies[i]->column, tiles[0][0]);
				//enemies[i]->path = star.Path(enemies[i]->row, enemies[i]->column, waypoints[j], tiles, lineSize);
		//	}
		//	else
		//	{
				//jobCreation(i, waypoints[j-1]->_row, waypoints[j-1]->_column, waypoints[j]);
				//enemies[i]->path = star.Path(waypoints[j - 1]->_row, waypoints[j - 1]->_column, waypoints[j], tiles, lineSize);
			//}
		//}
				//star.path.clear();
				//star.fullPath.clear();
	}

	SDL_Thread * thread1 = SDL_CreateThread(threaded, "T1", NULL);
	//SDL_Thread * thread2 = SDL_CreateThread(threaded, "T2", NULL);


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

	for (int i = 0; i < enemies.size(); i++)
	{
		delete enemies[i];
	}

	tiles.clear();
	renderer.destroy();
}

void Game::jobCreation(int index, int row, int col, Tile* goal)
{
	ThreadData Tdata;
	Tdata.index = index;
	Tdata._row = row;
	Tdata._col = col;
	Tdata.goal = goal;

	SDL_LockMutex(threadLock);
	jobQueue.push(Tdata);
	SDL_UnlockMutex(threadLock);
}

void Game::update()
{
	unsigned int currentTime = LTimer::gameTime();//millis since game started
	unsigned int deltaTime = currentTime - lastTime;//time since last update

	vector< vector<Tile*> >::iterator row;
	vector<Enemy*>::iterator i;
	vector<Tile*>::iterator col;
	
	//camera.pos.x = tileWidth * cameraCol;
	//camera.pos.y = tileHeight * cameraRow;

	for (row = tiles.begin(); row != tiles.end(); row++)
	{
		for (col = row->begin(); col != row->end(); col++)
		{
			(*col)->Update(deltaTime);
		}
	}

	for (i = enemies.begin(); i != enemies.end(); i++)
	{
		(*i)->Update(deltaTime);
	}
	//enemies[0]->Update(deltaTime);
	//enemies[1]->Update(deltaTime);
	//enemies[2]->Update(deltaTime);
	//enemies[3]->Update(deltaTime);

	lastTime = currentTime;
}

void Game::render()
{
	renderer.clear(Colour(0,0,0));

	//int cameraOffsetX = camera.pos.x * tileWidth;
	//int cameraOffsetY = camera.pos.y * tileHeight;

	vector< vector<Tile*> >::iterator row;
	vector<Tile*>::iterator col;

	for (row = tiles.begin(); row != tiles.end(); row++)
	{
		for (col = row->begin(); col != row->end(); col++)
		{
			(*col)->Render(renderer);
		}
	}

	//for (int row = camera.pos.y; row < (camera.size.h / tileHeight) + cameraOffsetY; row++)
	//{
	//	for (int col = camera.pos.x; col < (camera.size.w / tileWidth) + cameraOffsetX; col++)
	//	{
	//		tiles[row][col]->Render2(renderer, cameraOffsetX, cameraOffsetY);
	//	}
	//}

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
	if (evt == EventListener::Event::LEFT) {
		if (camera.pos.x >= 0)
		{
			//cameraCol -= 1;
			camera.pos.x -= 1;
		}
	}
	if (evt == EventListener::Event::RIGHT) {
		if (camera.pos.x +camera.size.w <= tiles[0][lineSize-1]->GetPosition().x)
		{
			//cameraCol += 1;
			camera.pos.x += 1;
		}
	}
	if (evt == EventListener::Event::UP) {
		if (camera.pos.y >= 0)
		{
			//cameraRow += 1;
			camera.pos.y += 1;
		}
	}
	if (evt == EventListener::Event::DOWN) {
		if (camera.pos.y + camera.size.h < tiles[lineSize-1][0]->GetPosition().y)
		{
			//cameraRow -= 1;
			camera.pos.y -= 1;
		}
	}
}
