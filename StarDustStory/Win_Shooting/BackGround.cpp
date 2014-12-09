
//------------------------------------------
#include "GameDef.h"
#include "sceneGame.h"
#include "sceneTitle.h"
#include "BackGround.h"

//------------------------------------------
#define BACKGROUND_WIDTH 800		// �w�i�摜�؂���T�C�Y ��
#define BACKGROUND_HEIGHT 1109		// �w�i�摜�؂���T�C�Y �c

#define BACKGROUND_WIDTH_NUM 1		// �w�i�J��Ԃ��� ��
#define BACKGROUND_HEIGHT_NUM 2		// �w�i�J��Ԃ��� �c
#define SCROLL_SPEED 200;			// �w�i�X�N���[���X�s�[�h

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
	if(FvBackGroundPos.y <= -BACKGROUND_HEIGHT*BACKGROUND_HEIGHT_NUM) FvBackGroundPos.y = 0;
}

//------------------------------------------
// Render
void TBackGround::Render(void)
{
	// �w�i�`�� �K���ɑS�̂𖄂ߌ�����	�r���[�|�[�g�ϊ����L���ɂȂ��Ă��Ȃ�
	RECT FrSrcRec = {0 , 0 , BACKGROUND_WIDTH , BACKGROUND_HEIGHT}; 	// �摜�̒�����؂�����W
	for(int j=0; j<BACKGROUND_WIDTH_NUM; ++j){
		for(int i=0; i< BACKGROUND_HEIGHT_NUM*2; ++i){;
			FpGame.FpBackGroundSprite->Render(&FrSrcRec, D3DXVECTOR3( (float)(j*BACKGROUND_WIDTH),(float)FvBackGroundPos.y+i*BACKGROUND_HEIGHT, 0), 1.f);
		}
	}
}