#include "GameDef.h"
#include "ObjPlayer.h"
#include "plGranVisor.h"

//---------------------------------------------------------------------
#define TRIMMING__IMAGE_LTX 9	// 
#define TRIMMING__IMAGE_LTY 9	// 
#define TRIMMING__IMAGE_RBX 51	// 
#define TRIMMING__IMAGE_RBY 51	// 


//----------
// TobjPlayer
//----------

//---------------------------------------------------------------------
// �R���X�g���N�^
TplGranVisor::TplGranVisor( TsceneGame *game, Vector2D position, double radius )
	:TobjPlayer(
	position, 
	radius, 
	Vector2D(), 
	60., 
	Vector2D(0., -1.), 
	1., 
	Vector2D(0.9, 0.9), 
	10.,
	10.0,
	10 ),
	FpGame(game),
	FiBeamPower(0),
	FiShotGauge(0),
	FiShotTime(0),
	FiBeamTime(0),
	pos(D3DXVECTOR3( (float)position.x, (float)position.y, 0)),
	FiImageWidth(TRIMMING__IMAGE_RBX - TRIMMING__IMAGE_LTX),
	FiImageHeight(TRIMMING__IMAGE_RBY - TRIMMING__IMAGE_LTY)

{
}

//---------------------------------------------------------------------
// �f�X�g���N�^
TplGranVisor::~TplGranVisor( void )
{
}

//---------------------------------------------------------------------
// �X�V
BOOL TplGranVisor::Update(double time_elapsed)
{
	WORD inputBuff = Input().InputBuff;
	WORD DowninputBuff = Input().DownInputBuff;
	
	static const int MinBeamPower = 150;
	static const int ShotMaxGauge = 150;
	static const int MaxShotTime = 10;
	static const int MaxBeamTime = 3;


	// �V���b�g
	if( inputBuff & KEY_Z ) {
		// �p���[������Ȃ��Ƃ��́A�V���b�g�𔭎�
		if( FiBeamPower < MinBeamPower ) {
			FiBeamPower++;
			FiShotGauge = ShotMaxGauge;
			if( FiShotTime == 0 )
				FpGame->CreateShot( 1, FvPosition, Vector2D(0,-1) );
		} else {
			// �p���[������Ă���΃r�[����ł�
			FiShotGauge = 0;		
			if( FiBeamTime == 0 ) 
				FpGame->CreateShot( 2, FvPosition, Vector2D(0,-1.0) );
		}
	} else {
		// �{�^���𗣂����Ƃ�
		FiBeamPower = 0;

		// �Q�[�W���c���Ă���ꍇ�A�V���b�g��ł�
		if(FiShotGauge > 0){
			//if(FiShotTime == 0)
			//	FpGame.CreateShot( 5, FvPosition , Vector2D(0,-1.0));
			FiShotGauge--;
		}
	}
	//-----------------
	// �f�o�b�O���[�h
	//-----------------

	// X�L�[�������ƓG�_���e�𐶐�
	if( inputBuff & KEY_X ) {
		FiShotGauge = ShotMaxGauge;
		if( FiShotTime == 0 ) FpGame->CreateShot( 3, FvPosition, Vector2D(0,-1) );
		else FiShotGauge = 0;
	}
	// A�L�[�������ƓG�z�[�~���O�e�𐶐�
	if( inputBuff & KEY_A ) {
		FiShotGauge = ShotMaxGauge;
		if( FiShotTime == 0 ) FpGame->CreateShot( 4, FvPosition, Vector2D(0,-1) );
		else FiShotGauge = 0;
	}
	// S�L�[�������ƕ����e�𐶐�
	if( inputBuff & KEY_S ) {
		FiShotGauge = ShotMaxGauge;
		if( FiShotTime == 0 ) FpGame->CreateShot( 5, FvPosition, Vector2D(0,-1) );
		else FiShotGauge = 0;
	}
	// D�L�[�������Ɣ����e�𐶐�
	if( inputBuff & KEY_D ) {
		FiShotGauge = ShotMaxGauge;
		if( FiShotTime == 0 ) FpGame->CreateShot( 7, FvPosition, Vector2D(0,-1) );
		else FiShotGauge = 0;
	}

	// �V���b�g�ƃr�[���̑ҋ@���Ԃ��X�V
	FiShotTime = (FiShotTime+1) % MaxShotTime;
	FiBeamTime = (FiBeamTime+1) % MaxBeamTime;

	// �ړ�
	if( inputBuff & KEY_UP   )
		FvVelocity.y = -20.;	else
	if( inputBuff & KEY_DOWN ) FvVelocity.y =  20.; else
	FvVelocity.y = 0.0;
	if( inputBuff & KEY_LEFT ) FvVelocity.x = -20.;	else
	if( inputBuff & KEY_RIGHT) FvVelocity.x =  20.; else
	FvVelocity.x = 0.0;

	// ���K��
	FvVelocity.Normalize();
	FvVelocity *= this->FdMaxSpeed;

	// �N�����v���s��
	if( FvPosition.x < this->dBoundingRadius -50) FvPosition.x = this->dBoundingRadius -50;
	if( FvPosition.x > (50 - this->dBoundingRadius) ) FvPosition.x = 50 - this->dBoundingRadius;
	if( FvPosition.y < this->dBoundingRadius -50) FvPosition.y = this->dBoundingRadius -50;
	if( FvPosition.y > (50 - this->dBoundingRadius) ) FvPosition.y = 50 - this->dBoundingRadius;

	if(FdVitality <= 0)
		return FALSE;

	return TRUE;

}

//---------------------------------------------------------------------
// �`��
void TplGranVisor::Render( void )
{
	std::vector<Vector2D> vec;
	vec.push_back(FvPosition);

	// �r���[�|�[�g�ϊ�
	FpGame->ViewPortTransform( vec );
	RECT srcRec =  { TRIMMING__IMAGE_LTX, TRIMMING__IMAGE_LTY, TRIMMING__IMAGE_RBX, TRIMMING__IMAGE_RBY};		// �摜�̒�����؂�����W
	pos = D3DXVECTOR3( (float)vec[0].x, (float)vec[0].y, 0);

	// �摜��\��������W
	FpGame->FpPlayerVisorSprite->RenderEx(
							&srcRec,
							pos,													// DrawPosition
							D3DXVECTOR3((float)FvScale.x , (float)FvScale.y, 1),					// Scaling
							D3DXVECTOR3(0, 0, 0),									// Rotation
							&D3DXVECTOR3 ((float)(FiImageWidth/2), (float)(FiImageHeight/2), 0),	// RotationCenter
							1.0,													// Alpha
							D3DCOLOR(1));													// ColorKey

}

//---------------------------------------------------------------------
// Cgdi�`��
void TplGranVisor::RenderCgdi()
{
	TBaseMovingObject::RenderCgdi();

#ifdef _DEBUG
	TCHAR String[0xff];

	std::vector<Vector2D> vec;
	vec.push_back(FvPosition);

	// �r���[�|�[�g�ϊ�
	FpGame->ViewPortTransform( vec );

	_stprintf_s(String, 0xFF, TEXT("HP=%f"),FdVitality);
	DxGraphics9().DrawString(String, vec[0].x-30, vec[0].y+15 ,D3DXCOLOR(1.0,1.0,1.0,1.0));
#endif

}

//--------------------------------------------------------------------