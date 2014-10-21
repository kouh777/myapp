#ifndef __TASKMANAGER_H__
#define __TASKMANAGER_H__

//--------------------------------------------------------
#include <list>

//--------------------------------------------------------
class _Task
{
	friend class TTaskManager;

private:
	int FiPriority;
	std::list<_Task *>::iterator FIterator;

public:
	_Task(int prio);
	virtual ~_Task(void){}
	virtual bool Execute( double ElapsedTime) = 0;
	virtual void Draw(void) = 0;
	virtual void DrawCgdi(void) = 0;
//	virtual void Render3D(void) = 0;
};

//--------------------------------------------------------
class TTaskManager
{
private:
	std::list<_Task *> FTasks;
	TTaskManager(void){}
	TTaskManager(const TTaskManager & );
	TTaskManager operator = (const TTaskManager & );

public:
	~TTaskManager( void ){ Clear(); }
	static TTaskManager &GetIsntance( void ) {
		static TTaskManager instance;
		return instance;
	}
	std::list <_Task *>::iterator AddList(_Task *ptask);
	void Update(double elapsedTime);
	void Draw(void);
	void DrawCgdi(void);
	void Clear(void);
};

//--------------------------------------------------------
inline TTaskManager &TaskManager( void ) { return TTaskManager::GetIsntance(); }

#endif //__TASKMANAGER_H__