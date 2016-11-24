#pragma once

#include <vector>

#include "Renderer.h"
#include "GameObject.h"
#include "InputManager.h"
#include "EventListener.h"
#include "Tile.h"

/** The game objct whic manages the game loop*/
class Game:public EventListener
{
	InputManager inputManager;
	Renderer renderer;

	std::vector<GameObject*> gameObjects;
	std::vector<Tile*> tiles;

	int MAXTILES;
	int line;
	int column;
	int lineSize;
	int yPos;

	int tileWidth;
	int tileHeight;

	unsigned int lastTime;//time of last update;

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

