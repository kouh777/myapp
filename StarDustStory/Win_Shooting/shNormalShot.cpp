#include "GameDef.h"
#include "shNormalShot.h"
#include "GameWorld.h"

//----------------------------------------------
#define TRIMMING__IMAGE_LTX 0	// 
#define TRIMMING__IMAGE_LTY 0	// 
#define TRIMMING__IMAGE_RBX 242	// 
#define TRIMMING__IMAGE_RBY 359	// 

//----------------------------------------------
TshNormalShot::TshNormalShot( const Vector2D &pos, const Vector2D &velocity)
	:TobjShot(
	Vector2D(pos.x,pos.y-2),	// position
	3,							// radius
	velocity,					// velocity
	60,							// max_speed
	Vec2DNormalize(velocity),	// heading
	1.,							// mass
	Vector2D(0.2, 0.15),		// scale
	10,							// turn_rate
	10,							// max_force
	1							// vitality
	),
	FiImageWidth(TRIMMING__IMAGE_RBX - TRIMMING__IMAGE_LTX),
	FiImageHeight(TRIMMING__IMAGE_RBY - TRIMMING__IMAGE_LTY)
{
}

//----------------------------------------------
TshNormalShot::~TshNormalShot(void)
{
}

//----------------------------------------------
BOOL TshNormalShot::Update(double time_elapsed)
{
	//----------
	// �����e(��ԕ����͌Œ�l)
	//----------
	FvVelocity.Normalize();
	FvVelocity *= FdMaxSpeed;

	if(FdVitality <= 0 || !Move(time_elapsed))
		return false;

	return true;
}

//----------------------------------------------
void TshNormalShot::Render( void )
{
	
	std::vector<Vector2D> vec;
	vec.push_back(FvPosition);

	// �r���[�|�[�g�ϊ�
	GameWorld().ViewPortTransform( vec );
	RECT srcRec =  { TRIMMING__IMAGE_LTX, TRIMMING__IMAGE_LTY, TRIMMING__IMAGE_RBX, TRIMMING__IMAGE_RBY};						// �摜�̒�����؂�����W
	pos = D3DXVECTOR3( (float)vec[0].x, (float)vec[0].y, 0);

	// �摜��\��������W
	GameWorld().FpShotSprite->RenderEx(
							&srcRec,
							pos,																	// DrawPosition
							D3DXVECTOR3((float)FvScale.x , (float)FvScale.y, 1),					// Scaling
							D3DXVECTOR3(0, 0, 0),													// Rotation
							&D3DXVECTOR3 ((float)(FiImageWidth/2), (float)(FiImageHeight/2), 0),	// RotationCenter
							1.0,																	// Alpha
							D3DCOLOR(1));															// ColorKey

}

//---------------------------------------------------------------------
// Cgdi�`��
void TshNormalShot::RenderCgdi()
{
	TBaseMovingObject::RenderCgdi();	
}