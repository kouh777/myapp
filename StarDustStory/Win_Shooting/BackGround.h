#ifndef __BACKGROUND_H__
#define __BACKGROUND_H__

//------------------------------------------
#include "GameDef.h"
#include "GameWorld.h"

//------------------------------------------------------------------------------------
#define BACKGROUND_WIDTH 256		// 背景画像切り取りサイズ 横
#define BACKGROUND_HEIGHT 96		// 背景画像切り取りサイズ 縦

#define BACKGROUND_WIDTH_NUM 4		// 背景繰り返し回数 横
#define BACKGROUND_HEIGHT_NUM 7		// 背景繰り返し回数 縦

#define SCROLL_SPEED 100;			// 背景スクロールスピード

//------------------------------------------------------------------------------------
#define CELL_SIZE 32;				// 一マスの大きさ

/*
struct StageSet{
	const int type;					// 種類
};

// マップチップの配置データ
StageSet StageArray[]=
{
	0, 1 , 2, 3, 4, 5, 6, 7 ,8, 9 , 10, 11, 0 , 1 , 2,  3, 4, 5, 6,
};
*/

//------------------------------------------------------------------------------------
class TBackGround
{
private:
	TBackGround( void );
	TBackGround( const TBackGround & );
	TBackGround operator = (const TBackGround &);
	Vector2D FvBackGroundPos;

public:
	~TBackGround(void);
	static TBackGround &GetInstance(void){
		static TBackGround instance;
		return instance;
	}
	void Render(void);
	void Update(double elapsedTime);
};

inline TBackGround &BackGround( void ) { return TBackGround::GetInstance(); }

//--------------------------------------------------------

#endif //__BACKGROUND_H__