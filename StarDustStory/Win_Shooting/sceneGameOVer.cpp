
//--------------------------------------------------------
#include "GameDef.h"
#include "sceneGameOver.h"
#include "cgdi.h"
#include "sceneTitle.h"
#include "sceneFade.h"

//--------------------------------------------------------
#define BACKGROUND_X 0			// wiæzuXÀW
#define BACKGROUND_Y 0			// wiæzuYÀW
#define BACKGROUND_WIDTH 640	// wiæØèæèTCY ¡
#define BACKGROUND_HEIGHT 480	// wiæØèæèTCY c

//--------------------------------------------------------
TsceneGameOver::TsceneGameOver(void):
	_Task(6),
	FiTimer(1),
	FbFadeFlg(FALSE),
	FpBackGameOver(NULL)
{
	// æðÉÇÝÞ
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
	// wi`æ KÉSÌðßÂ­·
	RECT FrSrcRec = {0 , 0 , BACKGROUND_WIDTH , BACKGROUND_HEIGHT}; 	// æÌ©çØèæéÀW
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