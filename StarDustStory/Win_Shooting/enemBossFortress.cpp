
#include "GameDef.h"
#include "enemBossFortress.h"
#include "BaseObserverObject.h"

#include "bulOneWay.h"
#include "bulHoming.h"
#include "bulAiming.h"

//---------------------------------------------------------------------
#define TRIMMING__IMAGE_LTX 10	// 
#define TRIMMING__IMAGE_LTY 300	// 
#define TRIMMING__IMAGE_RBX 38	// 
#define TRIMMING__IMAGE_RBY 328	// 

//----------------------------------------------
TenemBossFortress::TenemBossFortress( TsceneGame *game, const int &pattern, const Vector2D &pos, const Vector2D &velocity )
	:TsubjectEnemy(
	game,
	pos,						// position
	1.0,						// radius
	velocity,					// velocity
	0,							// max_speed
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
	bObserver = false;
	// このオブジェクトをenemBossSpaceShipのサブジェクトとして登録する
	const TBaseMovingObject *obj = FpGame->GetNewestEnemy();
	TBaseObserverObject *observer = (TBaseObserverObject*)obj;
	AddObserver( observer );
	observer->AddSubject(this);

	// オブジェクト向いている方向を受け取り描画するための計算
	FdRadian = atan2(FvVelocity.y ,FvVelocity.x);
	FdRadian /= D3DX_PI;
	FdRadian += 0.5;
	FdTheta = FdRadian * 180 ;
}

//----------------------------------------------
TenemBossFortress::~TenemBossFortress(void)
{

}

//---------------------------------------------
BOOL TenemBossFortress::Update(double time_elapsed)
{
	switch(FdPattern){	

		case 1:
			int test = 0;
			if (FdTimer < 20){
				FdTimer++;
				if(FdTimer >= 20){	
					for(int i=0; i < 5; ++i){
						FpGame->CreateBullet( 1, FvPosition, Vector2D(0+i*5,10));	
					}
					for(int i=0; i < 5; ++i){
						FpGame->CreateBullet( 1, FvPosition, Vector2D(0+i*(-5),10));	
					}
					FdTimer = 0;
				}
			}
			break;
	}
	FvVelocity.Normalize();
	FvSide = FvVelocity.Perp();
	FvVelocity *= FdMaxSpeed;

	if(FdVitality <= 0){

		// ボスに死亡を通知する
		std::list<TBaseObserverObject *>::iterator it;
		for( it=FObservers.begin() ; it !=FObservers.end(); it++  ){
			(*it)->RecieveNotify(this);
		}

		return FALSE;
	}

	return TRUE;
}

//---------------------------------------------
void TenemBossFortress::Render( void )
{
	std::vector<Vector2D> vec;
	vec.push_back(FvPosition);

	// ビューポート変換
	FpGame->ViewPortTransform( vec );
	RECT srcRec =  { TRIMMING__IMAGE_LTX, TRIMMING__IMAGE_LTY, TRIMMING__IMAGE_RBX, TRIMMING__IMAGE_RBY};						// 画像の中から切り取る座標
	pos = D3DXVECTOR3( (float)vec[0].x, (float)vec[0].y, 0);

	// 画像を表示する座標
	FpGame->FpBossSpaceshipSprite->RenderEx(
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
void TenemBossFortress::RenderCgdi()
{
	TBaseMovingObject::RenderCgdi();	
}

//---------------------------------------------