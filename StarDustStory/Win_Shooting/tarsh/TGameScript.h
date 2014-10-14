#ifndef __TGAMESCRIPT_H__
#define __TGAMESCRIPT_H__

#include <list>
#include "sll_string.h"
#include <TCHAR.h>

class TCommandBase;
class TGameWorld;
class StringList;

class TGameScript{
private:
	std::list<TCommandBase *> FlitCommand;
	int FiIndex;
	int FiWait;
public:
	TGameScript(TGameWorld *pworld);
	virtual ~TGameScript(void);
	bool Execute(void);
	void Clear(void);
	void Draw(void){}
	int CreateScript(StringList *plist);
	int ReadScriptFile(TCHAR *szFileName);
	int ReadScriptFromMemory(void);

	void SetWait(int time);
	void Pause(void){ FiWait = -1;}
	void Resume(void){ FiWait = 0;}
};

class TCommandBase
{
private:

public:
	TCommandBase();
	virtual ~TCommandBase(void){}
	virtual void Execute(void) = 0;
};

class TCmdEnemy:public TCommandBase
{
private:

public:
	TCmdEnemy();
	virtual ~TCmdEnemy();
	virtual void Execute(void);
};

class TCmdWait:public TCommandBase
{
private:
	TGameScript *FpScript;
	int FiTime;

public:
	TCmdWait( TGameScript *pScript, int time):FpScript(pScript),FiTime(time){}
	virtual ~TCmdWait(){}
	virtual void Execute(void){FpScript->SetWait(FiTime);}
};

#endif //__TGAMESCRIPT_H__