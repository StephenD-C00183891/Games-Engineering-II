//#pragma once
//
//#include "GameObject.h"
//#include "BasicTypes.h"
//#include "EventListener.h"
//#include "Enemy.h"
//#include <vector>
//#include <queue>
//
//class ThreadPool :public GameObject, public EventListener
//{
//
//public:
//
//	std::queue<Enemy*> enemyThread;
//
//	void Render(Renderer & r);
//
//	void Update(unsigned int deltaTime);
//
//	void onEvent(EventListener::Event);
//
//	void getJob();
//	void worker();
//	void addThread();
//
//
//};