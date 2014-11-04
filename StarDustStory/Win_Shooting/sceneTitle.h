#ifndef __TSCENETITLE_H__
#define __TSCENETITLE_H__

//--------------------------------------------------------
#include "TaskManager.h"

//--------------------------------------------------------
class TsceneTitle: public _Task
{
private:
	double FiTimer;

public:
	TsceneTitle(void):_Task(2),FiTimer(1){}
	virtual bool Execute( double ElapsedTime);
	virtual void Draw(void);
	virtual void DrawCgdi(void);
};

#endif //__TSCENETITLE_H__