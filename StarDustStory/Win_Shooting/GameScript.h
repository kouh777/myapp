
#ifndef __TSKSCRIPT_H__
#define __TSKSCRIPT_H__

//--------------------------------------------------------------------------------
#include <list>
#include <string>
#include "stringlist.h"

#define ENEM_BOX	1
#define ENEM_FISH	2 

//--------------------------------------------------------------------------------
class TGameWorld;
class TCommandBase;

//--------------------------------------------------------------------------------
// �G�̖��O
const static TCHAR* EnemyName_TBL[]={
	TEXT("1"),TEXT("2")
};

//--------------------------------------------------------------------------------
// �X�N���v�g�N���X
class TGameScript
{
private:
	TGameWorld				*FpGameWorld;
	std::list<TCommandBase *>	 FlitCommand;
	int							 FiIndex;
	int							 FiWait;

public:
	TGameScript( TGameWorld *pworld );
	virtual ~TGameScript( void );

	BOOL Excute( double fElapsedTime );
	void Draw( void ) {}


	void Clear( void );
	int CreateScript( TStringList *plist );
	int ReadScriptFile( TCHAR *szFileName );
	int ReadScriptFromMemory( void );


	void SetWait(int value) { FiWait = value; }
	void Pause( void ) { FiWait = -1; }
	void Resume( void ) { FiWait = 0; }

};

//--------------------------------------------------------------------------------
// �R�}���h���N���X
class TCommandBase 
{
private:
	
public:
	virtual ~TCommandBase( void ) {} 
	virtual void Excute( void ) = 0;
};

//--------------------------------------------------------------------------------
// �_�~�[�R�}���h�N���X
class TCmdDummy : public TCommandBase 
{
private:
	
public:
	TCmdDummy( void );
	virtual ~TCmdDummy( void ) {} 
	virtual void Excute( void );
};

//--------------------------------------------------------------------------------
// �G�R�}���h�N���X
class TCmdEnemy : public TCommandBase 
{
private:
	TGameWorld	*FpGameWorld;
	int				 FiType;		// �G�^�C�v
	int				 FiPattern;		// �G�s���p�^�[��
	double			 FdPosX;		// �G�o���ʒu��X���W
	double			 FdPosY;		// �G�o���ʒu��Y���W
	double			 FdVecX;		// �G�i�s������X���W
	double			 FdVecY;		// �G�i�s������Y���W
	//int		FiColor;		

public:
	TCmdEnemy( TGameWorld *pworld, int type, int pattern, Vector2D pos, Vector2D vec ):FpGameWorld(pworld), FiType(type), FiPattern(pattern),FdPosX(pos.x),FdPosY(pos.y),FdVecX(vec.x),FdVecY(vec.y){}
	virtual ~TCmdEnemy( void ) {} 
	virtual void Excute( void );
};

//--------------------------------------------------------------------------------
// �҂��R�}���h�N���X
class TCmdWait : public TCommandBase 
{
private:
	TGameScript *FpScript;
	int		FiTime;
	
public:
	TCmdWait( TGameScript *pScript, int time ):FpScript(pScript), FiTime(time) {}
	virtual ~TCmdWait( void ) {} 
	virtual void Excute( void ) { FpScript->SetWait( FiTime ); } 
};

//--------------------------------------------------------------------------------
#endif	// __TSKSCRIPT_H__