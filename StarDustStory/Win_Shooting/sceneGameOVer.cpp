
//--------------------------------------------------------
#include "GameDef.h"
#include "sceneGameOver.h"
#include "cgdi.h"
#include "sceneTitle.h"
#include "sceneFade.h"

//--------------------------------------------------------
#define BACKGROUND_X 0			// 背景画像配置X座標
#define BACKGROUND_Y 0			// 背景画像配置Y座標
#define BACKGROUND_WIDTH 640	// 背景画像切り取りサイズ 横
#define BACKGROUND_HEIGHT 480	// 背景画像切り取りサイズ 縦

//--------------------------------------------------------
TsceneGameOver::TsceneGameOver(void):
	_Task(6),
	FiTimer(1),
	FbFadeFlg(FALSE),
	FpBackGameOver(NULL)
{
	// 画像をメモリに読み込む
	FpBackGameOver = DxGraphics9().CreateSpriteFormFile(TEXT("game_over.png"),D3DFMT_A8R8G8B8 , D3DCOLOR_ARGB( 255, 255, 0, 0));
}

//--------------------------------------------------------
bool TsceneGameOver::Execute( double ElapsedTime)
{
	FiTimer -= ElapsedTime;
	if(FiTimer <= 0){
		if(FbFadeFlg == FALSE){
			new TsceneFade();
			FbFadeFlg = TRUE;
		}

		if(FiTimer <= -2.0){
			new TsceneTitle();
			return false;
		}
	}
	return true;
}

//--------------------------------------------------------
void TsceneGameOver::Draw(void)
{
	// 背景描画 適当に全体を埋め撃つくす
	RECT FrSrcRec = {0 , 0 , BACKGROUND_WIDTH , BACKGROUND_HEIGHT}; 	// 画像の中から切り取る座標
	D3DXVECTOR3* center = (0,0,0);

	FpBackGameOver->RenderEx(
						&FrSrcRec, 
						D3DXVECTOR3( (float)BACKGROUND_X,(float)BACKGROUND_Y, 0),
						D3DXVECTOR3(1.25,1.25,1.25),
						D3DXVECTOR3(0.0,0.0,0.0),
						center,
						1.0,
						1.0f
						);

}

//--------------------------------------------------------
void TsceneGameOver::DrawCgdi(void)
{

}