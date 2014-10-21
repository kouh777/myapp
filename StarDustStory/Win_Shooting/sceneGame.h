#ifndef __TSCENEGAME_H__
#define __TSCENEGAME_H__

//--------------------------------------------------------
#include "TaskManager.h"

//--------------------------------------------------------
class TsceneGame: public _Task
{
private:
	double FiTimer;

public:
	TsceneGame(void):_Task(2),FiTimer(3)
	{
	}
	virtual bool Execute( double ElapsedTime);
	virtual void Draw(void);
	virtual void DrawCgdi(void);
};

#endif //__TSCENEGAME_H__