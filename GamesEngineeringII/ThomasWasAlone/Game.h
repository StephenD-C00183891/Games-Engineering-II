#pragma once

#include <vector>

#include "Renderer.h"
#include "GameObject.h"
#include "InputManager.h"
#include "EventListener.h"
#include "Tile.h"
#include "Player.h"
#include "Enemy.h"
#include "astar.h"

/** The game objct whic manages the game loop*/
class Game:public EventListener
{
	InputManager inputManager;
	Renderer renderer;

	
	std::vector <Tile*> enemyPath;
	//std::vector<Tile*> waypoints;

	Rect camera;

	Player* p1;
	Size2D wS;

	//SDL_Thread * thread1;

	int MAXTILES;
	int line;
	int column;
	//int lineSize;

	int enemyCount;
	int cameraRow;
	int cameraCol;
	float tileWidth;
	float tileHeight;
	int wallSpawn;
	int spawnCount;

	unsigned int lastTime;

	bool pause;
	bool quit;

public:
	static int threaded(void * data);
	Game();
	~Game();

	bool init();
	void destroy();

	//static std::queue<ThreadData> jobQueue;

	void jobCreation(int index, int row, int col, Tile* goal);

	void update();
	void render();
	void loop();

	void onEvent(EventListener::Event);
};

