
#ifndef __TSKSCRIPT_H__
#define __TSKSCRIPT_H__

//--------------------------------------------------------------------------------
#include <list>
#include <string>
#include "stringlist.h"

//------------------------------------------
// 敵ID定義
#define ENEM_NO						0
#define ENEM_BOX					1
#define ENEM_FISH					2
#define ENEM_BOSS_FORTRESS			3	//	ステージ2ボス砲台
#define ENEM_BOSS_SPACESHITP		4	//	ステージ2ボス
#define ENEM_BOSS_RIGHT_WING		12	//	ステージ2ボス右翼
#define ENEM_BOSS_LEFT_WING			13	//	ステージ2ボス左翼

//--------------------------------------------------------------------------------
class TGameWorld;
class TCommandBase;

//--------------------------------------------------------------------------------
// 敵の名前
const static TCHAR* EnemyName_TBL[]={
	TEXT("1"),TEXT("2"),TEXT("3"),TEXT("4")
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
#endif	// __TSKSCRIPT_H__