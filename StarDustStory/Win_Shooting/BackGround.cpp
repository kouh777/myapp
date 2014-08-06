
//------------------------------------------
#include "BackGround.h"

//------------------------------------------
// constract
TBackGround::TBackGround(void)
	:FvBackGroundPos(Vector2D( 0, 0))
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
	// �w�i�`�� �K���ɑS�̂𖄂ߌ�����	�r���[�|�[�g�ϊ����L���ɂȂ��Ă��Ȃ�
	RECT FrSrcRec = {0 , 0 , BACKGROUND_WIDTH , BACKGROUND_HEIGHT}; 	// �摜�̒�����؂�����W
	for(int j=0; j<BACKGROUND_WIDTH_NUM; ++j){
		for(int i=0; i< BACKGROUND_HEIGHT_NUM*2; ++i){;
			GameWorld().FpBackGround->Render(&FrSrcRec, D3DXVECTOR3( (float)(j*BACKGROUND_WIDTH),(float)FvBackGroundPos.y+i*BACKGROUND_HEIGHT, 0), 1.f);
		}
	}
}