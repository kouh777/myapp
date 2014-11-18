

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
	:FpSceneGame( pworld ), FiWait(0)
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
		if( it == FlitCommand.end() ) return TRUE;	// 終了している
		
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
		// あとでdefineで切るとりあえずenembox
		case 0:
			switch(FiPattern){
				case 1:
					FpSceneGame->CreateEnemy(1, 1,Vector2D(FdPosX,FdPosY),Vector2D(FdVecX,FdVecY));
					break;
				case 2:
					FpSceneGame->CreateEnemy(1, 2,Vector2D(FdPosX,FdPosY),Vector2D(FdVecX,FdVecY));
					break;
				case 3:
					FpSceneGame->CreateEnemy(1, 3,Vector2D(FdPosX,FdPosY),Vector2D(FdVecX,FdVecY));
					break;
				case 4:
					FpSceneGame->CreateEnemy(1, 4,Vector2D(FdPosX,FdPosY),Vector2D(FdVecX,FdVecY));
					break;
			}
			break;

		// あとでdefineで切るとりあえずenemFish
		case 1:
			switch(FiPattern){
				case 1:
					FpSceneGame->CreateEnemy(2, 1,Vector2D(FdPosX,FdPosY),Vector2D(FdVecX,FdVecY));
					break;
				case 2:
					FpSceneGame->CreateEnemy(2, 2,Vector2D(FdPosX,FdPosY),Vector2D(FdVecX,FdVecY));
					break;
				case 3:
					FpSceneGame->CreateEnemy(2, 3,Vector2D(FdPosX,FdPosY),Vector2D(FdVecX,FdVecY));
					break;
				case 4:
					FpSceneGame->CreateEnemy(2, 4,Vector2D(FdPosX,FdPosY),Vector2D(FdVecX,FdVecY));
					break;
			}
			break;

		// あとでdefineで切るとりあえず、enemFortress
		case 2:
			switch(FiPattern){
				case 1:
					FpSceneGame->CreateEnemy(3, 1,Vector2D(FdPosX,FdPosY),Vector2D(FdVecX,FdVecY));
					break;
			}
			break;
	}
}


//--------------------------------------------------------------------------------