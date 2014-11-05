#ifndef __TSCENEGAMEOVER_H__
#define __TSCENEGAMEOVER_H__

//--------------------------------------------------------
#include "TaskManager.h"

//--------------------------------------------------------
class TsceneGameOver: public _Task
{
private:
	double FiTimer;

public:
	TsceneGameOver(void):_Task(2),FiTimer(1){}
	virtual bool Execute( double ElapsedTime);
	virtual void Draw(void);
	virtual void DrawCgdi(void);
};

#endif //__TSCENEGAMEOVER_H__