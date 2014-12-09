#ifndef __TSCENETITLE_H__
#define __TSCENETITLE_H__

//--------------------------------------------------------
#include "TaskManager.h"

class ISprite;
class TBackGround;

//--------------------------------------------------------
class TsceneTitle: public _Task
{
private:
	double	FiTimer;
	bool	FbFadeFlg;
	ISprite *FpBackGround;
	ISprite *FpLogo;

public:
	TsceneTitle(void);
	virtual bool Execute( double ElapsedTime);
	virtual void Draw(void);
	virtual void DrawCgdi(void);
};

#endif //__TSCENETITLE_H__