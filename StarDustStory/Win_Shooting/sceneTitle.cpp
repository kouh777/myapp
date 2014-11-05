
//--------------------------------------------------------
#include "GameDef.h"
#include "sceneTitle.h"
#include "cgdi.h"
#include "sceneGame.h"
#include "sceneFade.h"

//--------------------------------------------------------
#define BACKGROUND_X 0			// 背景画像配置X座標
#define BACKGROUND_Y 0			// 背景画像配置Y座標
#define BACKGROUND_WIDTH 800	// 背景画像切り取りサイズ 横
#define BACKGROUND_HEIGHT 600	// 背景画像切り取りサイズ 縦

#define LOGO_X 160			// ロゴ画像配置X座標
#define LOGO_Y 200			// ロゴ画像配置Y座標
#define LOGO_WIDTH 480		// ロゴ画像切り取りサイズ 横
#define LOGO_HEIGHT 135		// ロゴ画像切り取りサイズ 縦

//--------------------------------------------------------
TsceneTitle::TsceneTitle(void):
	_Task(6),
	FiTimer(1),
	FbFadeFlg(FALSE),
	FpBackGround(NULL),
	FpLogo(NULL)
{
	// 画像をメモリに読み込む
	FpBackGround = DxGraphics9().CreateSpriteFormFile(TEXT("space3.png"),D3DFMT_A8R8G8B8 , D3DCOLOR_ARGB( 255, 0, 0, 0)); 
	FpLogo = DxGraphics9().CreateSpriteFormFile(TEXT("logo.png"),D3DFMT_A8R8G8B8 , D3DCOLOR_ARGB( 255, 0, 0, 0)); 
}

//--------------------------------------------------------
bool TsceneTitle::Execute( double ElapsedTime)
{
	FiTimer -= ElapsedTime;
	if(FiTimer <= 0){
		if(FbFadeFlg == FALSE){
			new TsceneFade();
			FbFadeFlg = TRUE;
		}

		if(FiTimer <= -2.0){
			new TsceneGame();
			return false;
		}
	}
	return true;
}

//--------------------------------------------------------
void TsceneTitle::Draw(void)
{
	// 背景描画 適当に全体を埋め撃つくす	ビューポート変換が有効になっていない
	RECT FrSrcRec = {0 , 0 , BACKGROUND_WIDTH , BACKGROUND_HEIGHT}; 	// 画像の中から切り取る座標
	FpBackGround->Render(&FrSrcRec, D3DXVECTOR3( (float)BACKGROUND_X,(float)BACKGROUND_Y, 0), 1.f);

	RECT FrSrcRecLogo = {0 , 0 , LOGO_WIDTH , LOGO_HEIGHT}; 	// 画像の中から切り取る座標
	FpLogo->Render(&FrSrcRecLogo, D3DXVECTOR3( (float)LOGO_X,(float)LOGO_Y, 0), 1.f);
}

//--------------------------------------------------------
void TsceneTitle::DrawCgdi(void)
{

}