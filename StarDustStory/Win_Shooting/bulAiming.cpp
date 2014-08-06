
#include "GameDef.h"
#include "bulAiming.h"
#include "GameWorld.h"

#include "ObjPlayer.h"

//---------------------------------------------------------------------
#define TRIMMING__IMAGE_LTX 2	// 
#define TRIMMING__IMAGE_LTY 130	// 
#define TRIMMING__IMAGE_RBX 8	// 
#define TRIMMING__IMAGE_RBY 140	// 

//----------------------------------------------
TbulAiming::TbulAiming( const Vector2D &pos, const Vector2D &velocity)
	:TobjBullet(
	pos,						// position
	0.3,						// radius
	velocity,					// velocity
	30,							// max_speed
	Vec2DNormalize(velocity),	// heading
	0.,							// mass
	Vector2D(1., 1.),			// scale
	0,							// turn_rate
	1,							// max_force
	1							// vitality
	),
	FdRadian(0),
	FdTheta(0),
	FiImageWidth(TRIMMING__IMAGE_RBX - TRIMMING__IMAGE_LTX),
	FiImageHeight(TRIMMING__IMAGE_RBY - TRIMMING__IMAGE_LTY)
{
	const TobjPlayer *pPlayer = GameWorld().pPlayer;
	FvVelocity = pPlayer->vPosition - FvPosition;
	FvVelocity.Normalize();
	FvHeading = FvVelocity;
	FvSide = FvHeading.Perp();

	// �I�u�W�F�N�g�����Ă���������󂯎��`�悷�邽�߂̌v�Z
	FdRadian = atan2(FvHeading.y ,FvHeading.x);
	FdRadian /= D3DX_PI;
	FdRadian += 0.5;
	FdTheta = FdRadian * 180 ;
}

//----------------------------------------------
BOOL TbulAiming::Update(double time_elapsed)
{
	//----------
	// �ǂ������e(�v���C���[����������Ɍ���)
	//----------

//	radian = atan2f(FvHeading.y,FvHeading.x);			// FvHeading����摜�̉�]�p�����߂�
//	radian += D3DX_PI;

	FvVelocity.Normalize();
	FvVelocity *= FdMaxSpeed;

	if(FdVitality <= 0 )
		return FALSE;

	return TRUE;
}

//----------------------------------------------
void TbulAiming::Render( void )
{
	std::vector<Vector2D> vec;
	vec.push_back(FvPosition);

	// �r���[�|�[�g�ϊ�
	GameWorld().ViewPortTransform( vec );
	RECT srcRec =  { TRIMMING__IMAGE_LTX, TRIMMING__IMAGE_LTY, TRIMMING__IMAGE_RBX, TRIMMING__IMAGE_RBY};			
	pos = D3DXVECTOR3( (float)vec[0].x, (float)vec[0].y, 0);
	
	// �e�̌��ɂڂ���������
	GameWorld().FpSprites->RenderEx(
							&srcRec,
							pos,																// DrawPosition
							D3DXVECTOR3((float)(FvScale.x*1.5) , (float)(FvScale.y*1.5), 1),				// Scaling
							D3DXVECTOR3(0, 0, 0),												// Rotation
							&D3DXVECTOR3 ((float)(FiImageWidth/2), (float)(FiImageHeight/2), 0),	// RotationCenter
							0.4,																// Alpha
							D3DCOLOR(1));	


	// �摜��\��������W
	GameWorld().FpSprites->RenderEx(
							&srcRec,
							pos,													// DrawPosition
							D3DXVECTOR3((float)FvScale.x , (float)FvScale.y, 1),					// Scaling
							D3DXVECTOR3(0, 0, 0),									// Rotation
							&D3DXVECTOR3 ((float)(FiImageWidth/2), (float)(FiImageHeight/2), 0),		// RotationCenter
							1.0,													// Alpha
							D3DCOLOR(1));													// ColorKey

}

//---------------------------------------------------------------------
// Cgdi�`��
void TbulAiming::RenderCgdi()
{
	TBaseMovingObject::RenderCgdi();	
}

//----------------------------------------------