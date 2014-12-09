#ifndef __TSCENEGAMEOVER_H__
#define __TSCENEGAMEOVER_H__

//--------------------------------------------------------
#include "TaskManager.h"

//--------------------------------------------------------
class TsceneGameOver: public _Task
{
private:
	ISprite *FpBackGameOver;
	BOOL FbFadeFlg;
	double FiTimer;

public:
	TsceneGameOver(void);
	virtual bool Execute( double ElapsedTime);
	virtual void Draw(void);
	virtual void DrawCgdi(void);
};

#endif //__TSCENEGAMEOVER_H__