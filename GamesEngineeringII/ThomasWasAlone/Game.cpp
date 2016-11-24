#include "stdafx.h"

#include <iostream>
using namespace std;



#include "LTimer.h"
#include "SpinningBox.h"
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


	//create some game objects

	SpinningBox* box1 = new SpinningBox(Rect(5,0,4,0.2f));
	box1->col = Colour(255, 255, 0);
	box1->angVel = 0.5f;//radian per seconds	
	SpinningBox* box2 = new SpinningBox(Rect(5, 0, 1, 1));
	box2->angVel = -0.85f;//radian per seconds
	box2->col = Colour(50, 255, 255);
	SpinningBox* box3 = new SpinningBox(Rect(0, 0, 1, 1));
	box3->angVel = -0.1f;//radian per seconds	
	box3->col = Colour(200, 100, 255);
	SpinningBox* box4 = new SpinningBox(Rect(0, 0, 1, 1));
	box4->angVel = .0f;//radian per seconds	

	//calibration check: this box should be just inside bottom left of window
	SpinningBox* box5 = new SpinningBox(Rect(-vpWidth/2, (-vpWidth / 2) / aspectRatio, 1, 1));
	box5->col = Colour(255,0,0);//red
	//calibration check: this box should be just inside top right of window
	SpinningBox* box6 = new SpinningBox(Rect((vpWidth / 2)-1, ((vpWidth / 2) / aspectRatio) -1, 1, 1));
	box6->col = Colour(255, 100, 0);//orange


	//add out boxes to the gameworld
	gameObjects.push_back(box1);
	gameObjects.push_back(box2);
	gameObjects.push_back(box3);
	gameObjects.push_back(box4);
	gameObjects.push_back(box5);
	gameObjects.push_back(box6);

	
	lastTime = LTimer::gameTime();

	//we want this box to respond to REVERSE event
	inputManager.AddListener(EventListener::Event::REVERSE, box1);

	//want game loop to pause
	inputManager.AddListener(EventListener::Event::PAUSE, this);
	inputManager.AddListener(EventListener::Event::QUIT, this);

	return true;

}


void Game::destroy()
{
	//empty out the game object vector before quitting
	for (std::vector<GameObject*>::iterator i = gameObjects.begin(); i != gameObjects.end(); i++) {
		delete *i;
	}
	gameObjects.clear();
	renderer.destroy();
}

//** calls update on all game entities*/
void Game::update()
{
	unsigned int currentTime = LTimer::gameTime();//millis since game started
	unsigned int deltaTime = currentTime - lastTime;//time since last update

	//call update on all game objects
	for (std::vector<GameObject*>::iterator i = gameObjects.begin(); i != gameObjects.end(); i++) {
		(*i)->Update(deltaTime);
	}

	//save the curent time for next frame
	lastTime = currentTime;
}

//** calls render on all game entities*/

void Game::render()
{
	renderer.clear(Colour(0,0,0));// prepare for new frame
	
	//render every object
	for (std::vector<GameObject*>::iterator i = gameObjects.begin(), e= gameObjects.end(); i != e; i++) {
		(*i)->Render(renderer);
	}

	renderer.present();// display the new frame (swap buffers)

	
}

/** update and render game entities*/
void Game::loop()
{
	LTimer capTimer;//to cap framerate

	int frameNum = 0;
	while (!quit) { //game loop
		capTimer.start();

		inputManager.ProcessInput();

		if(!pause) //in pause mode don't bother updateing
			update();
		render();

		int frameTicks = capTimer.getTicks();//time since start of frame
		if (frameTicks < SCREEN_TICKS_PER_FRAME)
		{
			//Wait remaining time before going to next frame
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
