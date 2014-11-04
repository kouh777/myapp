#include "GameDef.h"
#include "shBlastShot.h"

//----------------------------------------------
#define TRIMMING__IMAGE_LTX 40	// 
#define TRIMMING__IMAGE_LTY 20	// 
#define TRIMMING__IMAGE_RBX 60	// 
#define TRIMMING__IMAGE_RBY 30	//

//----------------------------------------------
TshBlastShot::TshBlastShot( TsceneGame *game, const Vector2D &pos, const Vector2D &velocity)
	:TobjShot(
	Vector2D(pos.x,pos.y-2),	// position
	1.5,						// radius
	velocity,					// velocity
	50,							// max_speed
	Vec2DNormalize(velocity),	// heading
	1.,							// mass
	Vector2D(2.0, 2.0),			// scale
	10,							// turn_rate
	10,							// max_force
	1							// vitality
	),
	FpGame(game),
	FdRadian(0),
	FdTheta(0),
	FiImageWidth(TRIMMING__IMAGE_RBX - TRIMMING__IMAGE_LTX),
	FiImageHeight(TRIMMING__IMAGE_RBY - TRIMMING__IMAGE_LTY)
{
	// �I�u�W�F�N�g�����Ă���������󂯎��`�悷�邽�߂̌v�Z
	FdRadian = atan2(FvVelocity.y ,FvVelocity.x);
	FdTheta = (FdRadian/D3DX_PI+0.5) * 180 ;
}

//----------------------------------------------
TshBlastShot::~TshBlastShot(void)
{
}

//----------------------------------------------
BOOL TshBlastShot::Update(double time_elapsed)
{
	//----------
	// �����e(�G�ɓ�����Δ������N����)
	//----------
	FvVelocity.Normalize();
	FvVelocity *= FdMaxSpeed;	

	if(FdVitality <= 0){
		FpGame->CreateShot( 8, FvPosition, Vector2D( 0, 0) );
		return false;
	}
	
	if(!Move(time_elapsed))
		return false;

	return true;
}

//----------------------------------------------
void TshBlastShot::Render( void )
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
							pos,																	// DrawPosition
							D3DXVECTOR3((float)FvScale.x , (float)FvScale.y, 1),					// Scaling
							D3DXVECTOR3(0, 0, FdTheta),													// Rotation
							&D3DXVECTOR3 ((float)(FiImageWidth/2), (float)(FiImageHeight/2), 0),	// RotationCenter
							1.0,																	// Alpha
							D3DCOLOR(1));															// ColorKey

}

//---------------------------------------------------------------------
// Cgdi�`��
void TshBlastShot::RenderCgdi()
{
	TBaseMovingObject::RenderCgdi();	
}