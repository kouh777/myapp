
#include "GameDef.h"
#include "enemBossSpaceship.h"
#include "enemBossFortress.h"

#include "bulOneWay.h"
#include "bulHoming.h"
#include "bulAiming.h"

//---------------------------------------------------------------------
#define TRIMMING__IMAGE_LTX 10	// 
#define TRIMMING__IMAGE_LTY 395	// 
#define TRIMMING__IMAGE_RBX 365	// 
#define TRIMMING__IMAGE_RBY 558	// 

//----------------------------------------------
TenemBossSpaceship::TenemBossSpaceship( TsceneGame *game, const int &pattern, const Vector2D &pos, const Vector2D &velocity )
	:TobserverEnemy(
	game,
	pos,						// position
	2.0,						// radius
	velocity,					// velocity
	0,							// max_speed
	Vec2DNormalize(velocity),	// heading
	0.,							// mass
	Vector2D(1.,1.),			// scale
	0,							// turn_rate
	1,							// max_force
	100							// vitality
	),
	FdPattern(pattern),
	FdTimer(0),
	FmTurnFlag(false),
	FbInitializeFlg(false),
	FiImageWidth(TRIMMING__IMAGE_RBX - TRIMMING__IMAGE_LTX),
	FiImageHeight(TRIMMING__IMAGE_RBY - TRIMMING__IMAGE_LTY),
	FbDamageFlg(false)
{
}

//----------------------------------------------
TenemBossSpaceship::~TenemBossSpaceship(void)
{

}

//----------------------------------------------
void TenemBossSpaceship::Initialize(void)
{
	// �C��𐶐�����
	FpGame->CreateEnemy( 3 , 1 , Vector2D(FvPosition.x-13,FvPosition.y-7) , Vector2D(FvVelocity.x,FvVelocity.y) );
	FpGame->CreateEnemy( 3 , 1 , Vector2D(FvPosition.x+13,FvPosition.y-7) , Vector2D(FvVelocity.x,FvVelocity.y) );
}

//---------------------------------------------
BOOL TenemBossSpaceship::Update(double time_elapsed)
{
	if( !FbInitializeFlg){
		Initialize();
		FbInitializeFlg = true;
	}

	switch(FdPattern){	

		case 1:
			if (FdTimer < 20){
				FdTimer++;
				if(FdTimer >= 20){
					FpGame->CreateBullet( 1, FvPosition, Vector2D(0,10));	
					for(int i=0; i < 3; ++i){
						FpGame->CreateBullet( 1, FvPosition, Vector2D(0+i*5,10));	
					}
					for(int i=0; i < 3; ++i){
						FpGame->CreateBullet( 1, FvPosition, Vector2D(0+i*(-5),10));	
					}
					//FpGame.CreateBullet( 2, FvPosition, Vector2D(0 ,10));
					FpGame->CreateBullet( 5, FvPosition, Vector2D(0 ,10));
					FdTimer = 0;
				}
			}
			break;
	}

	FvVelocity.Normalize();
	FvSide = FvVelocity.Perp();
	FvVelocity *= FdMaxSpeed;

	// �I�u�W�F�N�g�����Ă���������󂯎��`�悷�邽�߂̌v�Z
	FdRadian = atan2(FvVelocity.y ,FvVelocity.x);
	FdRadian /= D3DX_PI;
//	FdRadian += 0.5;
	FdTheta = FdRadian * 180 ;

	/*
	// iterator����
	std::list<TBaseSubjectObject *>::iterator it;
	for(it = FSubjects.begin(); it != FSubjects.end(); it++){
		(*it)->Update(time_elapsed);
	}
	*/

	if(FdVitality <= 0){
		return FALSE;
	}

	return TRUE;
}

//---------------------------------------------
void TenemBossSpaceship::Render( void )
{
	std::vector<Vector2D> vec;
	vec.push_back(FvPosition);

	// �r���[�|�[�g�ϊ�
	FpGame->ViewPortTransform( vec );
	RECT srcRec =  { TRIMMING__IMAGE_LTX, TRIMMING__IMAGE_LTY, TRIMMING__IMAGE_RBX, TRIMMING__IMAGE_RBY};						// �摜�̒�����؂�����W
	pos = D3DXVECTOR3( (float)vec[0].x, (float)vec[0].y, 0);

	// �摜��\��������W
	FpGame->FpBossSpaceshipSprite->RenderEx(
							&srcRec,
							pos,												// DrawPosition
							D3DXVECTOR3((float)FvScale.x , (float)FvScale.y, 1),				// Scaling
							D3DXVECTOR3(0, 0, (float)-FdTheta),								// Rotation
							&D3DXVECTOR3 ((float)(FiImageWidth/2), (float)(FiImageHeight/2), 0),	// RotationCenter
							1.0,												// Alpha
							D3DCOLOR(1));												// ColorKey

	/*
	// SubjectObject��iterator����
	std::list<TBaseSubjectObject *>::iterator it;
	for(it = FSubjects.begin(); it != FSubjects.end(); it++){
		(*it)->Render();
	}
	*/

}

//---------------------------------------------------------------------
// Cgdi�`��
void TenemBossSpaceship::RenderCgdi()
{
	TBaseMovingObject::RenderCgdi();	
}

//---------------------------------------------

void TenemBossSpaceship::RecieveNotify( TBaseSubjectObject *sub )
{
	::OutputDebugString( TEXT("Success! (TBaseObserverObject::RecieveNotify())\n") );
}