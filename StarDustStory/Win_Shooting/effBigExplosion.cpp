

#include "GameDef.h"
//-------------------------------------------
#include "objEffect.h"
#include "effBigExplosion.h"

//----------------------------------------------
#define TRIMMING__IMAGE_LTX 92	// 
#define TRIMMING__IMAGE_LTY 43	// 
#define TRIMMING__IMAGE_RBX 118	// 
#define TRIMMING__IMAGE_RBY 66	// 

//----------------------------------------------
TeffBigExplosion::TeffBigExplosion( TsceneGame *game, const Vector2D &pos, const Vector2D &velocity)
	:TobjEffect(
	game,
	pos,						// position
	0.5,						// radius
	velocity,					// velocity
	0.5,						// max_speed
	Vec2DNormalize(velocity),	// heading
	0.,							// mass
	Vector2D(1.0, 1.0),			// scale
	0,							// turn_rate
	1,							// max_force
	1							// vitality
	),
	FiTimer(0),
	FiAlpha(1.0)
{
	iImageWidth=TRIMMING__IMAGE_RBX - TRIMMING__IMAGE_LTX;
	iImageHeight=TRIMMING__IMAGE_RBY - TRIMMING__IMAGE_LTY;

	// �{�X�Ǝ��̔������𔭐�
	int ch = PlayDxSound( SND_SE_BOSS_DEATH );
	int bgm_vol = GetVolume(ch);
	SetVolume(ch, -300);
}

//----------------------------------------------
TeffBigExplosion::~TeffBigExplosion(void)
{
}

//----------------------------------------------
BOOL TeffBigExplosion::Update(double time_elapsed)
{
	//----------
	// ����
	//----------
	const double dExplosionSpeed = 5;
	FiTimer += time_elapsed;
	FvScale.x += time_elapsed * dExplosionSpeed;
	FvScale.y += time_elapsed * dExplosionSpeed;
	if( FiTimer > 0.2 ){
		FiAlpha -= time_elapsed;
		if( FiAlpha < 0 )
			FiAlpha = 0;
	}
	FvVelocity.Normalize();
	FvVelocity *= FdMaxSpeed;

	if(FiAlpha <= 0 || !Move(time_elapsed))
		return false;

	return true;
}

//----------------------------------------------
void TeffBigExplosion::Render( void )
{
	std::vector<Vector2D> vec;
	vec.push_back(FvPosition);

	// �r���[�|�[�g�ϊ�
	FpGame->ViewPortTransform( vec );
	RECT srcRec =  { TRIMMING__IMAGE_LTX, TRIMMING__IMAGE_LTY, TRIMMING__IMAGE_RBX, TRIMMING__IMAGE_RBY};						// �摜�̒�����؂�����W
	pos = D3DXVECTOR3( (float)vec[0].x, (float)vec[0].y, 0);

	// �摜��\��������W
	FpGame->FpSprites->RenderEx(
							&srcRec,
							pos,																// DrawPosition
							D3DXVECTOR3((float)FvScale.x , (float)FvScale.y, 1),				// Scaling
							D3DXVECTOR3(0, 0, 0),												// Rotation
							&D3DXVECTOR3 ((float)(FiImageWidth/2), (float)(FiImageHeight/2), 0),	// RotationCenter
							FiAlpha,																// Alpha
							D3DCOLOR(1));																// ColorKey
}

//---------------------------------------------------------------------
// Cgdi�`��
void TeffBigExplosion::RenderCgdi()
{
	TBaseMovingObject::RenderCgdi();	
}