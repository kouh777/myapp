

#include "GameDef.h"
#include "sceneGame.h"

#include <fstream>
#include <vector>
#include "GameScript.h"

//--------------------------------------------------------------------------------
using namespace std;

//--------------------------------------------------------------------------------
// コンストラクタ
TGameScript::TGameScript( TsceneGame *pworld )
	:FpSceneGame( pworld ), FiWait(0),FbMove(TRUE)
{
}

//--------------------------------------------------------------------------------
// デストラクタ
TGameScript::~TGameScript( void )
{
	Clear();
}

//--------------------------------------------------------------------------------
// 実行関数
BOOL TGameScript::Excute( double fElapsedTime )
{
	if( FiWait > 0 )	FiWait--;	

	if( FiWait == 0 ) { 
		list<TCommandBase *>::iterator it = FlitCommand.begin();
		if( it == FlitCommand.end() )
			return TRUE;
		
		(*it)->Excute();	// 実行

		// 先頭削除
		delete (*it);		
		FlitCommand.pop_front();
	}
	return TRUE;
}

//--------------------------------------------------------------------------------
// リストクリア
void TGameScript::Clear( void )
{
	list<TCommandBase *>::iterator it; // イテレータ
	for( it=FlitCommand.begin(); it!=FlitCommand.end(); it++ ) {
		delete (*it);
	}
	FlitCommand.clear();
}

//--------------------------------------------------------------------------------
// スクリプト作成
int TGameScript::CreateScript( TStringList *plist )
{
	TStringList		commaString;
	int				result			= 0;
	int				lines			= plist->GetCount(); 
	BOOL			comment			= FALSE;				// comment
	static const	int enemt_cnt	= sizeof(EnemyName_TBL)/sizeof(TCHAR *);

	for( int i=0; i<lines; i++ ) {
		int cnt = commaString.CommaText( (*plist)[i] ); 	
		if( cnt <= 0 ) continue;

		const wstring command	= commaString[0];  
		
		//-----------
		// コメント
		//-----------
		if( command.find( TEXT("//"), 0 ) == 0 ) continue;
		if( command.find( TEXT("*/"), 0 ) == 0 ) {
			comment = FALSE;
			continue;
		} else
		if( command.find( TEXT("/*"), 0 ) == 0 ) comment = TRUE;
		if( comment ) continue;

		//---------------
		// コマンド解析
		//---------------

		// 敵
		if( _tcsicmp(command.c_str(), TEXT("enemy")) == 0 ) {
			const wstring param1	= commaString[1]; 
			const wstring param2	= commaString[2];
			const wstring param3	= commaString[3];
			const wstring param4	= commaString[4];
			const wstring param5	= commaString[5];
			const wstring param6	= commaString[6];

			wstring param7 = TEXT("0");
			if( commaString.GetCount() > 7 ) {
				param7 = commaString[4]; 
			}

			for( int n=0; n<enemt_cnt; n++) {
				if( _tcsicmp(param1.c_str(), EnemyName_TBL[n]) == 0 ) {
					FlitCommand.push_back( new TCmdEnemy(
												FpSceneGame,
												n,
												_wtof(param2.c_str()),
												Vector2D(_wtof(param3.c_str()),_wtof(param4.c_str())),
												Vector2D(_wtof(param5.c_str()),_wtof(param6.c_str()))
					) );	
					result++;
					break;
				}
			}
		}else
		// 待機
		if( _tcsicmp(command.c_str(), TEXT("wait")) == 0 ) {
			const wstring param1	= commaString[1];  

			FlitCommand.push_back( new TCmdWait(this, _wtoi(param1.c_str()) ) );	
			result++;
		}
		else
		// 終了
		if( _tcsicmp(command.c_str(), TEXT("clear")) == 0 ) {
			FlitCommand.push_back( new TCmdEnd(this) );	
			result++;
//			FbMove = TRUE;
		}
	}
	return -1;
}

//--------------------------------------------------------------------------------
// スクリプトファイル読み込み
int TGameScript::ReadScriptFile( TCHAR *szFileName )
{
	TStringList strlist;
	
	// クリア
	Clear();

	strlist.ReadFromFile( szFileName );
	return CreateScript( &strlist );
}

//--------------------------------------------------------------------------------
int TGameScript::ReadScriptFromMemory( void )
{
	return -1;
}


//---------------
// TCmdEnemy
//---------------

//--------------------------------------------------------------------------------
void TCmdEnemy::Excute( void )
{
	switch(FiType)
	{
		// enembox
		case 0:
			FpSceneGame->CreateEnemy(ENEM_BOX, FiPattern,Vector2D(FdPosX,FdPosY),Vector2D(FdVecX,FdVecY));
			break;

		// enemFish
		case 1:
			FpSceneGame->CreateEnemy(ENEM_FISH, FiPattern,Vector2D(FdPosX,FdPosY),Vector2D(FdVecX,FdVecY));
			break;

		// enemFortress
		case 2:
			FpSceneGame->CreateEnemy(ENEM_BOSS_FORTRESS, FiPattern,Vector2D(FdPosX,FdPosY),Vector2D(FdVecX,FdVecY));
			break;

		// enemBossSpaceShip
		case 3:
			FpSceneGame->CreateEnemy(ENEM_BOSS_SPACESHITP, FiPattern,Vector2D(FdPosX,FdPosY),Vector2D(FdVecX,FdVecY));
			break;

		// enemBossDegin
		case 4:
			FpSceneGame->CreateEnemy(ENEM_BOSS_DEGIN, FiPattern,Vector2D(FdPosX,FdPosY),Vector2D(FdVecX,FdVecY));
			break;

		// enemBossUnderson
		case 5:
			FpSceneGame->CreateEnemy(ENEM_BOSS_UNDERSON, FiPattern,Vector2D(FdPosX,FdPosY),Vector2D(FdVecX,FdVecY));
			break;

		// enemBossShadowVisor
		case 6:
			FpSceneGame->CreateEnemy(ENEM_BOSS_SHADOW_VISOR, FiPattern,Vector2D(FdPosX,FdPosY),Vector2D(FdVecX,FdVecY));
			break;

		// enemBossShadowSaber
		case 7:
			FpSceneGame->CreateEnemy(ENEM_BOSS_SHADOW_SABER, FiPattern,Vector2D(FdPosX,FdPosY),Vector2D(FdVecX,FdVecY));
			break;

		// enemBossAlbert
		case 8:
			FpSceneGame->CreateEnemy(ENEM_BOSS_ALBERT, FiPattern,Vector2D(FdPosX,FdPosY),Vector2D(FdVecX,FdVecY));
			break;

		// enemCommet
		case 9:
			FpSceneGame->CreateEnemy(ENEM_COMMET, FiPattern,Vector2D(FdPosX,FdPosY),Vector2D(FdVecX,FdVecY));
			break;

	}
}


//--------------------------------------------------------------------------------