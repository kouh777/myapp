#ifndef __BACKGROUND_H__
#define __BACKGROUND_H__

//------------------------------------------------------------------------------------
/*
#define BACKGROUND_WIDTH 256		// 背景画像切り取りサイズ 横
#define BACKGROUND_HEIGHT 96		// 背景画像切り取りサイズ 縦

#define BACKGROUND_WIDTH_NUM 4		// 背景繰り返し回数 横
#define BACKGROUND_HEIGHT_NUM 7		// 背景繰り返し回数 縦
*/
#define BACKGROUND_WIDTH 800		// 背景画像切り取りサイズ 横
#define BACKGROUND_HEIGHT 600		// 背景画像切り取りサイズ 縦

#define BACKGROUND_WIDTH_NUM 1		// 背景繰り返し回数 横
#define BACKGROUND_HEIGHT_NUM 2		// 背景繰り返し回数 縦


#define SCROLL_SPEED 200;			// 背景スクロールスピード

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
	Vector2D FvBackGroundPos;
	TsceneGame FpGame;

public:
	TBackGround(TsceneGame &game );
	~TBackGround(void);
	void Render(void);
	void Update(double elapsedTime);
};

//--------------------------------------------------------

#endif //__BACKGROUND_H__