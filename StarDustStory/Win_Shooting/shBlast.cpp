#include "GameDef.h"
#include "shBlast.h"
#include "GameWorld.h"

//----------------------------------------------
#define TRIMMING__IMAGE_LTX 0	// 
#define TRIMMING__IMAGE_LTY 40	// 
#define TRIMMING__IMAGE_RBX 30	// 
#define TRIMMING__IMAGE_RBY 70	//

//----------------------------------------------
TshBlast::TshBlast( TsceneGame *game, const Vector2D &pos, const Vector2D &velocity)
	:TobjShot(
	game,
	Vector2D(pos.x,pos.y),		// position
	3,							// radius
	velocity,					// velocity
	1,							// max_speed
	Vec2DNormalize(velocity),	// heading
	1.,							// mass
	Vector2D(0, 0),				// scale
	10,							// turn_rate
	10,							// max_force
	1							// vitality
	),
	FdRadian(0),
	FdTheta(0),
	FdTimer(0),
	FdInitialRadius(FdBoundingRadius),
	FiImageWidth(TRIMMING__IMAGE_RBX - TRIMMING__IMAGE_LTX),
	FiImageHeight(TRIMMING__IMAGE_RBY - TRIMMING__IMAGE_LTY)
{
	// オブジェクト向いている方向を受け取り描画するための計算
	FdRadian = atan2(FvVelocity.y ,FvVelocity.x);
	FdTheta = (FdRadian/D3DX_PI+0.5) * 180 ;
}

//----------------------------------------------
TshBlast::~TshBlast(void)
{
}

//----------------------------------------------
BOOL TshBlast::Update(double time_elapsed)
{
	//----------
	// 爆風(徐々に大きくなり、最大の大きさになれば消える)
	//----------
	const double dBlastTime = 1;
	const double fMaxScaling = 3;

	FvVelocity.Normalize();
	FvVelocity *= FdMaxSpeed;
	FdTimer += time_elapsed * FdMaxSpeed;
	
	FvScale.x = FdTimer*(1/dBlastTime) * fMaxScaling;
	FvScale.y = FdTimer*(1/dBlastTime) * fMaxScaling;
	FdBoundingRadius = FdInitialRadius * FvScale.x;

	if( ( FdTimer > dBlastTime ) | ( !Move(time_elapsed) ) )
		return false;

	return true;
}

//----------------------------------------------
void TshBlast::Render( void )
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
void TshBlast::RenderCgdi()
{
	TBaseMovingObject::RenderCgdi();	
}