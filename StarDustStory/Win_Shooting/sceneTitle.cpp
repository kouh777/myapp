
//--------------------------------------------------------
#include "GameDef.h"
#include "sceneTitle.h"
#include "cgdi.h"
#include "sceneGame.h"
#include "sceneFade.h"

//--------------------------------------------------------
#define BACKGROUND_X 0			// �w�i�摜�z�uX���W
#define BACKGROUND_Y 0			// �w�i�摜�z�uY���W
#define BACKGROUND_WIDTH 800	// �w�i�摜�؂���T�C�Y ��
#define BACKGROUND_HEIGHT 600	// �w�i�摜�؂���T�C�Y �c

#define LOGO_X 160			// ���S�摜�z�uX���W
#define LOGO_Y 200			// ���S�摜�z�uY���W
#define LOGO_WIDTH 480		// ���S�摜�؂���T�C�Y ��
#define LOGO_HEIGHT 135		// ���S�摜�؂���T�C�Y �c

//--------------------------------------------------------
TsceneTitle::TsceneTitle(void):
	_Task(6),
	FiTimer(1),
	FbFadeFlg(FALSE),
	FpBackGround(NULL),
	FpLogo(NULL)
{
	// �摜���������ɓǂݍ���
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
	// �w�i�`�� �K���ɑS�̂𖄂ߌ�����	�r���[�|�[�g�ϊ����L���ɂȂ��Ă��Ȃ�
	RECT FrSrcRec = {0 , 0 , BACKGROUND_WIDTH , BACKGROUND_HEIGHT}; 	// �摜�̒�����؂�����W
	FpBackGround->Render(&FrSrcRec, D3DXVECTOR3( (float)BACKGROUND_X,(float)BACKGROUND_Y, 0), 1.f);

	RECT FrSrcRecLogo = {0 , 0 , LOGO_WIDTH , LOGO_HEIGHT}; 	// �摜�̒�����؂�����W
	FpLogo->Render(&FrSrcRecLogo, D3DXVECTOR3( (float)LOGO_X,(float)LOGO_Y, 0), 1.f);
}

//--------------------------------------------------------
void TsceneTitle::DrawCgdi(void)
{

}