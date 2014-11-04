#include "GameDef.h"
#include "TaskManager.h"

//--------------------------------------------------------
// constructor
_Task::_Task(int prio)
	:FiPriority(prio)
{
	FIterator = TaskManager().AddList(this);
}

//--------------------------------------------------------
// Add Task
std::list <_Task *>::iterator TTaskManager:: AddList(_Task *ptask)
{
	std::list<_Task *>::iterator it;
	for(it = FTasks.begin(); it != FTasks.end(); it++){
		if( (*it)->FiPriority <= ptask->FiPriority ){
			return FTasks.insert(it, ptask);
		}
	}
	FTasks.push_back(ptask);
	it = FTasks.end();
	return --it;
}

//--------------------------------------------------------
// Initialize
void TTaskManager::Initialize( HWND hWnd, int cx, int cy )
{
	FhWnd = hWnd;
	FiClientX = cx;
	FiClientY = cy;
}

//--------------------------------------------------------
void TTaskManager::Update(double elapsedTime)
{
	std::list<_Task *>::iterator it;
	for(it = FTasks.begin(); it!= FTasks.end(); ){
		if((*it)->Execute(elapsedTime) == false){
			delete(*it);
			it = FTasks.erase(it);
			continue;
		}
		it++;
	}
}

//--------------------------------------------------------
void TTaskManager::Draw(void)
{
	std::list<_Task *>::iterator it;
	for(it = FTasks.begin(); it!= FTasks.end(); it++){
		(*it)->Draw();
	}
}

//--------------------------------------------------------
void TTaskManager::DrawCgdi(void)
{
	std::list<_Task *>::iterator it;
	for(it = FTasks.begin(); it!= FTasks.end(); it++){
		(*it)->DrawCgdi();
	}
}

//--------------------------------------------------------
void TTaskManager::Clear(void)
{
	std::list<_Task *>::iterator it;
	for(it = FTasks.begin(); it!= FTasks.end(); it++){
		delete *it;
	}
	FTasks.clear();
}