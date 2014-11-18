#include "GameDef.h"
#include "shAimingShot.h"
#include "GameWorld.h"

//----------------------------------------------
#define TRIMMING__IMAGE_LTX 40	// 
#define TRIMMING__IMAGE_LTY 20	// 
#define TRIMMING__IMAGE_RBX 60	// 
#define TRIMMING__IMAGE_RBY 30	//

//----------------------------------------------
TshAimingShot::TshAimingShot( TsceneGame *game, const Vector2D &pos, const Vector2D &velocity)
	:TobjShot(
	game,
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
	FdTheta(0),
	FiImageWidth(TRIMMING__IMAGE_RBX - TRIMMING__IMAGE_LTX),
	FiImageHeight(TRIMMING__IMAGE_RBY - TRIMMING__IMAGE_LTY)
{
	// When this shots create, get nearset enemy.
	const TBaseMovingObject *FpEnemy = NULL;
	if(FpGame->GetNearestEnemy() != NULL)
		FpEnemy = FpGame->GetNearestEnemy();
	if(FpEnemy)
		FvVelocity = FpEnemy->vPosition - FvPosition;
	else
		FvVelocity = Vector2D(0, -1);
	FvVelocity.Normalize();
	FvVelocity *= FdMaxSpeed;

	// オブジェクト向いている方向を受け取り描画するための計算
	FdRadian = atan2(FvVelocity.y ,FvVelocity.x);
	FdRadian /= D3DX_PI;
	FdRadian += 0.5;
	FdTheta = FdRadian * 180 ;

}

//----------------------------------------------
TshAimingShot::~TshAimingShot(void)
{
}

//----------------------------------------------
BOOL TshAimingShot::Update(double time_elapsed)
{

	if(FdVitality <= 0 || !Move(time_elapsed))
		return false;

	return true;
}

//----------------------------------------------
void TshAimingShot::Render( void )
{
	
	std::vector<Vector2D> vec;
	vec.push_back(FvPosition);

	// ビューポート変換
	FpGame->ViewPortTransform( vec );
	RECT srcRec =  { TRIMMING__IMAGE_LTX, TRIMMING__IMAGE_LTY, TRIMMING__IMAGE_RBX, TRIMMING__IMAGE_RBY};						// 画像の中から切り取る座標
	pos = D3DXVECTOR3( (float)vec[0].x, (float)vec[0].y, 0);

	// 画像を表示する座標
	FpGame->FpSprites->RenderEx(
							&srcRec,
							pos,																	// DrawPosition
							D3DXVECTOR3((float)FvScale.x , (float)FvScale.y, 1),					// Scaling
							D3DXVECTOR3(0, 0, (float)FdTheta),													// Rotation
							&D3DXVECTOR3 ((float)(FiImageWidth/2), (float)(FiImageHeight/2), 0),	// RotationCenter
							1.0,																	// Alpha
							D3DCOLOR(1));															// ColorKey

}

//---------------------------------------------------------------------
// Cgdi描画
void TshAimingShot::RenderCgdi()
{
	TBaseMovingObject::RenderCgdi();	
}