
#include "GameDef.h"
#include "enemBox.h"
#include "GameWorld.h"

#include "bulOneWay.h"
#include "bulHoming.h"
#include "bulAiming.h"

//---------------------------------------------------------------------
#define TRIMMING__IMAGE_LTX 0	// 
#define TRIMMING__IMAGE_LTY 0	// 
#define TRIMMING__IMAGE_RBX 20	// 
#define TRIMMING__IMAGE_RBY 20	// 

//----------------------------------------------
TenemBox::TenemBox( const int &pattern, const Vector2D &pos, const Vector2D &velocity )
	:TobjEnemy(
	pos,						// position
	0.9,						// radius
	velocity,					// velocity
	30,							// max_speed
	Vec2DNormalize(velocity),	// heading
	0.,							// mass
	Vector2D(1.,1.),			// scale
	0,							// turn_rate
	1,							// max_force
	5							// vitality
	),
	FdPattern(pattern),
	FdTimer(0),
	FmTurnFlag(false),
	FiImageWidth(TRIMMING__IMAGE_RBX - TRIMMING__IMAGE_LTX),
	FiImageHeight(TRIMMING__IMAGE_RBY - TRIMMING__IMAGE_LTY)
{
	// �I�u�W�F�N�g�����Ă���������󂯎��`�悷�邽�߂̌v�Z
	FdRadian = atan2(FvHeading.y ,FvHeading.x);
	FdRadian /= D3DX_PI;
	FdRadian += 0.5;
	FdTheta = FdRadian * 180 ;
}

//----------------------------------------------
TenemBox::~TenemBox(void)
{

}

//---------------------------------------------
BOOL TenemBox::Update(double time_elapsed)
{
	switch(FdPattern){	

		case 1:
			if (FdTimer < 20){
				FdTimer++;
				if(FdTimer >= 20){
					GameWorld().CreateBullet( 1, FvPosition, Vector2D(0,10));	
					for(int i=0; i < 3; ++i){
						GameWorld().CreateBullet( 1, FvPosition, Vector2D(0+i*5,10));	
					}
					for(int i=0; i < 3; ++i){
						GameWorld().CreateBullet( 1, FvPosition, Vector2D(0+i*(-5),10));	
					}
					GameWorld().CreateBullet( 2, FvPosition, Vector2D(0 ,10));
					GameWorld().CreateBullet( 3, FvPosition, Vector2D(0 ,10));
					FdTimer = 0;
				}
			}
			break;

		case 2:
			if (FdTimer < 20){
				FdTimer++;
				if(FdTimer >= 20){
					GameWorld().CreateBullet( 2, FvPosition, Vector2D(0 ,10));
					GameWorld().CreateBullet( 3, FvPosition, Vector2D(0 ,10));
					FdTimer = 0;
				}
			}
			break;

		case 3:
			if(!FmTurnFlag && FvPosition.y > 0){
				GameWorld().CreateBullet( 3, FvPosition, Vector2D(0 ,10));
				FvVelocity *= -1;
				FmTurnFlag = true;

			}
			if(FmTurnFlag == true && FvPosition.y < -40){
				FvVelocity *= -1;
				FmTurnFlag = false;				
			}
			break;

		case 4:
			if (FdTimer < 20){
				FdTimer++;
				if(FdTimer >= 20){
					GameWorld().CreateBullet( 1, FvPosition, Vector2D(0 ,1));
					FdTimer = 0;
				}
			}			
			break;

	}

	FvVelocity.Normalize();
	FvSide = FvVelocity.Perp();
	FvVelocity *= FdMaxSpeed;

	if(FdVitality <= 0){
		return FALSE;
	}

	return TRUE;
}

//---------------------------------------------
void TenemBox::Render( void )
{
	std::vector<Vector2D> vec;
	vec.push_back(FvPosition);

	// �r���[�|�[�g�ϊ�
	GameWorld().ViewPortTransform( vec );
	RECT srcRec =  { TRIMMING__IMAGE_LTX, TRIMMING__IMAGE_LTY, TRIMMING__IMAGE_RBX, TRIMMING__IMAGE_RBY};						// �摜�̒�����؂�����W
	pos = D3DXVECTOR3( (float)vec[0].x, (float)vec[0].y, 0);

	// �摜��\��������W
	GameWorld().FpSprites->RenderEx(
							&srcRec,
							pos,												// DrawPosition
							D3DXVECTOR3((float)FvScale.x , (float)FvScale.y, 1),				// Scaling
							D3DXVECTOR3(0, 0, 0),								// Rotation
							&D3DXVECTOR3 ((float)(FiImageWidth/2), (float)(FiImageHeight/2), 0),	// RotationCenter
							1.0,												// Alpha
							D3DCOLOR(1));												// ColorKey

}

//---------------------------------------------------------------------
// Cgdi�`��
void TenemBox::RenderCgdi()
{
	TBaseMovingObject::RenderCgdi();	
}

//---------------------------------------------