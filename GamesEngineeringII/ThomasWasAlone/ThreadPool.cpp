#include "stdafx.h"

#include "ThreadPool.h"


ThreadPool::ThreadPool(): threadLock(SDL_CreateMutex()), semaphore(SDL_CreateSemaphore(0)), conditional(SDL_CreateCond())
{

}

ThreadPool::~ThreadPool()
{

}

Enemy* ThreadPool::getJob()
{
	if (enemyQueue.size() > 0)
	{
		Enemy * e = enemyQueue.front();
		enemyQueue.pop();
		return e;
	}
}

int ThreadPool::getWorker(void *data)
{


	return 0;
}

void ThreadPool::fillQueue(Enemy * enemy)
{
	SDL_mutexP(threadLock);
	enemyQueue.push(enemy);
	SDL_mutexV(threadLock);
}

SDL_mutex * ThreadPool::getLock()
{
	return threadLock;
}

SDL_semaphore * ThreadPool::getSemaphore()
{
	return semaphore;
}

SDL_cond * ThreadPool::getConditional()
{
	return conditional;
}