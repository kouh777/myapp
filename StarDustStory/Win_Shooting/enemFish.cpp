
#include "GameDef.h"
#include "enemFish.h"
#include "GameWorld.h"

#include "bulOneWay.h"
#include "bulHoming.h"
#include "bulAiming.h"

//---------------------------------------------------------------------
#define TRIMMING__IMAGE_LTX 10	// 
#define TRIMMING__IMAGE_LTY 10	// 
#define TRIMMING__IMAGE_RBX 40	// 
#define TRIMMING__IMAGE_RBY 40	// 

//----------------------------------------------
TenemFish::TenemFish( TsceneGame *game, const int &pattern, const Vector2D &pos, const Vector2D &velocity )
	:TobserverEnemy(
	game,
	pos,						// position
	0.9,						// radius
	velocity,					// velocity
	30,							// max_speed
	Vec2DNormalize(velocity),	// heading
	0.,							// mass
	Vector2D(1.,1.),			// scale
	0,							// turn_rate
	1,							// max_force
	1							// vitality
	),
	FdPattern(pattern),
	FdTimer(0),
	FmTurnFlag(false),
	FiImageWidth(TRIMMING__IMAGE_RBX - TRIMMING__IMAGE_LTX),
	FiImageHeight(TRIMMING__IMAGE_RBY - TRIMMING__IMAGE_LTY)
{
}

//----------------------------------------------
TenemFish::~TenemFish(void)
{

}

//---------------------------------------------
BOOL TenemFish::Update(double time_elapsed)
{
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

		case 2:
			if (FdTimer < 20){
				FdTimer++;
				if(FdTimer >= 20){
					//FpGame.CreateBullet( 2, FvPosition, Vector2D(0 ,10));
					FpGame->CreateBullet( 3, FvPosition, Vector2D(0 ,10));
					FdTimer = 0;
				}
			}
			break;

		case 3:
			if(!FmTurnFlag && FvPosition.y > 0){
				FpGame->CreateBullet( 5, FvPosition, Vector2D(0 ,1));
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
					FpGame->CreateBullet( 1, FvPosition, Vector2D(0 ,1));
					FdTimer = 0;
				}
			}			
			break;

	}

	FvVelocity.Normalize();
	FvSide = FvVelocity.Perp();
	FvVelocity *= FdMaxSpeed;

	// オブジェクト向いている方向を受け取り描画するための計算
	FdRadian = atan2(FvVelocity.y ,FvVelocity.x);
	FdRadian /= D3DX_PI;
	FdRadian += 0.5;
	FdTheta = FdRadian * 180 ;

	if(FdVitality <= 0){
		// 爆発エフェクトを表示させる
		FpGame->CreateEffect(EFF_EXPLOSION, FvPosition, FvVelocity);
		return FALSE;
	}

	return TRUE;
}

//---------------------------------------------
void TenemFish::Render( void )
{
	std::vector<Vector2D> vec;
	vec.push_back(FvPosition);

	// ビューポート変換
	FpGame->ViewPortTransform( vec );
	RECT srcRec =  { TRIMMING__IMAGE_LTX, TRIMMING__IMAGE_LTY, TRIMMING__IMAGE_RBX, TRIMMING__IMAGE_RBY};						// 画像の中から切り取る座標
	pos = D3DXVECTOR3( (float)vec[0].x, (float)vec[0].y, 0);

	// 画像を表示する座標
	FpGame->FpEnemySprite->RenderEx(
							&srcRec,
							pos,												// DrawPosition
							D3DXVECTOR3((float)FvScale.x , (float)FvScale.y, 1),				// Scaling
							D3DXVECTOR3(0, 0, (float)-FdTheta),								// Rotation
							&D3DXVECTOR3 ((float)(FiImageWidth/2), (float)(FiImageHeight/2), 0),	// RotationCenter
							1.0,												// Alpha
							D3DCOLOR(1));												// ColorKey

}

//---------------------------------------------------------------------
// Cgdi描画
void TenemFish::RenderCgdi()
{
	TBaseMovingObject::RenderCgdi();	
}

//---------------------------------------------

void TenemFish::RecieveNotify( TBaseSubjectObject *sub ){

}