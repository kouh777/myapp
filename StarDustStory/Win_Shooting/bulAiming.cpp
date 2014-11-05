
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
TbulAiming::TbulAiming( TsceneGame *game, const Vector2D &pos, const Vector2D &velocity)
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
	FpGame(game),
	FdRadian(0),
	FdTheta(0),
	FiImageWidth(TRIMMING__IMAGE_RBX - TRIMMING__IMAGE_LTX),
	FiImageHeight(TRIMMING__IMAGE_RBY - TRIMMING__IMAGE_LTY)
{
	const TobjPlayer *pPlayer = FpGame->pPlayer;
	if(pPlayer)
		FvVelocity = pPlayer->vPosition - FvPosition;
	else
		FvVelocity = Vector2D(0,1.0);
	FvVelocity.Normalize();
	FvHeading = FvVelocity;
	FvSide = FvHeading.Perp();
}

//----------------------------------------------
BOOL TbulAiming::Update(double time_elapsed)
{
	//----------
	// 追い撃ち弾(プレイヤーがいる方向に撃つ)
	//----------

	FvVelocity.Normalize();
	FvVelocity *= FdMaxSpeed;

	// オブジェクト向いている方向を受け取り描画するための計算
	FdRadian = atan2(FvVelocity.y ,FvVelocity.x);
	FdRadian /= D3DX_PI;
	FdRadian += 0.5;
	FdTheta = FdRadian * 180 ;

	if(FdVitality <= 0 )
		return FALSE;

	return TRUE;
}

//----------------------------------------------
void TbulAiming::Render( void )
{
	std::vector<Vector2D> vec;
	vec.push_back(FvPosition);

	// ビューポート変換
	FpGame->ViewPortTransform( vec );
	RECT srcRec =  { TRIMMING__IMAGE_LTX, TRIMMING__IMAGE_LTY, TRIMMING__IMAGE_RBX, TRIMMING__IMAGE_RBY};			
	pos = D3DXVECTOR3( (float)vec[0].x, (float)vec[0].y, 0);

	// 画像を表示する座標
	FpGame->FpSprites->RenderEx(
							&srcRec,
							pos,													// DrawPosition
							D3DXVECTOR3((float)FvScale.x , (float)FvScale.y, 1),					// Scaling
							D3DXVECTOR3(0, 0, FdTheta),									// Rotation
							&D3DXVECTOR3 ((float)(FiImageWidth/2), (float)(FiImageHeight/2), 0),		// RotationCenter
							1.0,													// Alpha
							D3DCOLOR(1));	
}

//---------------------------------------------------------------------
// Cgdi描画
void TbulAiming::RenderCgdi()
{
	TBaseMovingObject::RenderCgdi();	
}

//----------------------------------------------