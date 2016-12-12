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

	std::vector<std::vector<Tile*>> tiles;
	std::vector <Enemy*> enemies; 
	std::vector <Tile*> enemyPath;

	Player* p1;
	Size2D wS;
	astar star;

	int MAXTILES;
	int line;
	int column;
	int lineSize;

	int enemyCount;
	int i;
	float tileWidth;
	float tileHeight;
	int wallSpawn;
	int spawnCount;

	unsigned int lastTime;

	bool pause;
	bool quit;

public:
	Game();
	~Game();

	bool init();
	void destroy();

	void update();
	void render();
	void loop();

	void onEvent(EventListener::Event);
};

