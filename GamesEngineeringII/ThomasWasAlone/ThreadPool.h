#pragma once

#include "GameObject.h"
#include "BasicTypes.h"
#include "EventListener.h"
#include "Enemy.h"
#include <vector>
#include <queue>
#include <functional>
#include <thread>


class ThreadPool
{

public:

	ThreadPool();
	~ThreadPool();


	Enemy* getJob();

	int getWorker(void * data);

	void fillQueue(Enemy * enemy);

	SDL_mutex * threadLock;
	SDL_semaphore * semaphore;
	SDL_cond * conditional;

	SDL_mutex * getLock();
	SDL_semaphore * getSemaphore();
	SDL_cond * getConditional();


};