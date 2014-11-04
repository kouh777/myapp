#ifndef __TASKMANAGER_H__
#define __TASKMANAGER_H__

//--------------------------------------------------------
#include <Windows.h>
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
	HWND FhWnd;
	int FiClientX;
	int FiClientY;
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
	void Initialize( HWND hWnd, int cx, int cy );
	void Update(double elapsedTime);
	void Draw(void);
	void DrawCgdi(void);
	void Clear(void);

	// アクセサ
	__declspec( property(get=GetiClientX) ) HWND FhWnd;
	HWND GethWnd( void ) const { return FhWnd; }
	__declspec( property(get=GetiClientX) ) int iClientX;
	int GetiClientX( void ) const { return FiClientX; }
	__declspec( property(get=GetiClientY) ) int iClientY;
	int GetiClientY( void ) const { return FiClientY; }
};

//--------------------------------------------------------
inline TTaskManager &TaskManager( void ) { return TTaskManager::GetIsntance(); }

#endif //__TASKMANAGER_H__