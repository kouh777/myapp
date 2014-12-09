
#ifndef __TSKSCRIPT_H__
#define __TSKSCRIPT_H__

//--------------------------------------------------------------------------------
#include "GameDef.h"
#include <list>
#include <string>
#include "stringlist.h"

//--------------------------------------------------------------------------------
class TGameWorld;
class TCommandBase;

//--------------------------------------------------------------------------------
// 敵の名前
const static TCHAR* EnemyName_TBL[]={
	TEXT("ENEM_BOX"),
	TEXT("ENEM_FISH"),
	TEXT("ENEM_BOSS_FORTRESS"),
	TEXT("ENEM_BOSS_SPACESHITP"),
	TEXT("ENEM_BOSS_DEGIN"),			
	TEXT("ENEM_BOSS_UNDERSON"),		
	TEXT("ENEM_BOSS_SHADOW_VISOR"),	
	TEXT("ENEM_BOSS_SHADOW_SABER"),	
	TEXT("ENEM_BOSS_ALBERT"),		
	TEXT("ENEM_COMMET"),
};

//--------------------------------------------------------------------------------
// スクリプトクラス
class TGameScript
{
private:
	TsceneGame					*FpSceneGame;
	std::list<TCommandBase *>	 FlitCommand;
	int							 FiIndex;
	int							 FiWait;
	BOOL						FbMove;

public:
	TGameScript( TsceneGame *pworld );
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

	void SetMove(bool move){ FbMove= move; }

};

//--------------------------------------------------------------------------------
// コマンド基底クラス
class TCommandBase 
{
private:
	
public:
	virtual ~TCommandBase( void ) {} 
	virtual void Excute( void ) = 0;
};

//--------------------------------------------------------------------------------
// ダミーコマンドクラス
class TCmdDummy : public TCommandBase 
{
private:
	
public:
	TCmdDummy( void );
	virtual ~TCmdDummy( void ) {} 
	virtual void Excute( void );
};

//--------------------------------------------------------------------------------
// 敵コマンドクラス
class TCmdEnemy : public TCommandBase 
{
private:
	TsceneGame		*FpSceneGame;
	int				 FiType;		// 敵タイプ
	int				 FiPattern;		// 敵行動パターン
	double			 FdPosX;		// 敵出現位置のX座標
	double			 FdPosY;		// 敵出現位置のY座標
	double			 FdVecX;		// 敵進行方向のX座標
	double			 FdVecY;		// 敵進行方向のY座標
	//int		FiColor;		

public:
	TCmdEnemy( TsceneGame *pworld, int type, int pattern, Vector2D pos, Vector2D vec ):FpSceneGame(pworld), FiType(type), FiPattern(pattern),FdPosX(pos.x),FdPosY(pos.y),FdVecX(vec.x),FdVecY(vec.y){}
	virtual ~TCmdEnemy( void ) {} 
	virtual void Excute( void );
};

//--------------------------------------------------------------------------------
// 待ちコマンドクラス
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
// 終了コマンドクラス
class TCmdEnd : public TCommandBase 
{
private:
	TGameScript *FpScript;
	
public:
	TCmdEnd( TGameScript *pScript ):FpScript(pScript) { pScript->SetMove(FALSE); }
	virtual ~TCmdEnd( void ) {} 
	virtual void Excute( void ) {  } 
};

//--------------------------------------------------------------------------------
#endif	// __TSKSCRIPT_H__