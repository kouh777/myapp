
//------------------------------------------
//------------------------------------------
#include "GameDef.h"
#include "sceneGame.h"
#include "BackGround.h"

//------------------------------------------
// constract
TBackGround::TBackGround( TsceneGame &game )
	:FvBackGroundPos(Vector2D( 0, 0))
	,FpGame(game)
{

}

//------------------------------------------
// destract
TBackGround::~TBackGround(void)
{

}

//------------------------------------------
// Update
void TBackGround::Update(double elapsedTime)
{ 
	FvBackGroundPos.y -= elapsedTime * SCROLL_SPEED;
	if(FvBackGroundPos.y <= -BACKGROUND_HEIGHT*7) FvBackGroundPos.y = 0;
}

//------------------------------------------
// Render
void TBackGround::Render(void)
{
	// 背景描画 適当に全体を埋め撃つくす	ビューポート変換が有効になっていない
	RECT FrSrcRec = {0 , 0 , BACKGROUND_WIDTH , BACKGROUND_HEIGHT}; 	// 画像の中から切り取る座標
	for(int j=0; j<BACKGROUND_WIDTH_NUM; ++j){
		for(int i=0; i< BACKGROUND_HEIGHT_NUM*2; ++i){;
			FpGame.FpBackGroundSprite->Render(&FrSrcRec, D3DXVECTOR3( (float)(j*BACKGROUND_WIDTH),(float)FvBackGroundPos.y+i*BACKGROUND_HEIGHT, 0), 1.f);
		}
	}
}