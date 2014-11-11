
//--------------------------------------------------------
#include "DirectGraphics9.h"
#include "cgdi.h"
#include "isprite.h"
#include "sceneFade.h"
#include "sceneGame.h"

//--------------------------------------------------------
// constructor
TsceneFade::TsceneFade(void):
	_Task(3),
	FiTimer(1),
	FpFade(NULL),
	FfAlpha(0.0f),
	bFlg(false),
	bFlg2(false),
	bFlg3(false)
{
	FpFade = DxGraphics9().CreateSpriteFormFile(TEXT("fade.png"),D3DFMT_A8R8G8B8 , D3DCOLOR_ARGB( 255, 0, 0, 0));
}

//--------------------------------------------------------
// destructor
TsceneFade::~TsceneFade()
{
	if(FpFade) FpFade = NULL; delete FpFade;	
}

//--------------------------------------------------------
bool TsceneFade::Execute( double ElapsedTime)
{
	const double fade_in_speed = 0.8f;		// �t�F�[�h�C���X�s�[�h
	const double fade_out_speed = 0.9f;		// �t�F�[�h�A�E�g�X�s�[�h
	const double fade_wait_time = -1.0f;	// �t�F�[�h�x��

	FiTimer -= ElapsedTime;

	// �t�F�[�h�A�E�g
	if(bFlg == false){
		FfAlpha += (float)( ElapsedTime * fade_out_speed );
		if(FfAlpha >= 1.0f){
			FfAlpha = 1.0f;
			bFlg = true;
		}
	}
	
	// �t�F�[�h�C��
	if(bFlg == true && FiTimer <= fade_wait_time){
		FfAlpha -= (float)( ElapsedTime * fade_in_speed );
		if(FfAlpha <= 0.0f){			
			return false;
		}
	}

	return true;
}

//--------------------------------------------------------
void TsceneFade::Draw(void)
{
	// �w�i�`�� �K���ɑS�̂𖄂ߌ�����
	RECT FrSrcRec = {0 , 0 , 10 , 10}; 	// �摜�̒�����؂�����W
	D3DXVECTOR3 center = D3DXVECTOR3(0,0,0);
	FpFade->RenderEx(
		&FrSrcRec,
		D3DXVECTOR3(0.0f,0.0f,0.0f),
		D3DXVECTOR3(100.0f, 100.0f, 1.0f),
		D3DXVECTOR3(0,0,0),
		&center,
		FfAlpha,
		1
		);
}

//--------------------------------------------------------
void TsceneFade::DrawCgdi(void)
{
//	Cgdi().TextOutAtPos(Vector2D(200,200), TEXT("Fade"));
}