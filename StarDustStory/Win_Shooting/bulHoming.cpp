
#include "GameDef.h"
#include "bulHoming.h"
#include "GameWorld.h"

#include "ObjPlayer.h"

//---------------------------------------------------------------------
#define TRIMMING__IMAGE_LTX 20	// 
#define TRIMMING__IMAGE_LTY 20	// 
#define TRIMMING__IMAGE_RBX 40	// 
#define TRIMMING__IMAGE_RBY 40	// 

//----------------------------------------------
TbulHoming::TbulHoming( TsceneGame *game, const Vector2D &pos , const Vector2D &velocity)
	:TobjBullet(
	game,
	pos,						// position
	0.6,						// radius
	velocity,					// velocity
	30,							// max_speed
	Vec2DNormalize(velocity),	// heading
	0.,							// mass
	Vector2D(1. , 1.),			// scale
	0,							// turn_rate
	1,							// max_force
	1							// vitality
	),
	FiImageWidth(TRIMMING__IMAGE_RBX - TRIMMING__IMAGE_LTX),
	FiImageHeight(TRIMMING__IMAGE_RBY - TRIMMING__IMAGE_LTY)
{
}

//----------------------------------------------
BOOL TbulHoming::Update(double time_elapsed)
{
	//----------
	// 追跡弾(プレイヤーがいる方向を追跡する)
	//----------
	const TobjPlayer *pPlayer = FpGame->pPlayer;
	FvVelocity = pPlayer->vPosition - FvPosition;
	FvVelocity.Normalize();
	FvHeading = FvVelocity;
	FvSide = FvHeading.Perp();
	FvVelocity *= FdMaxSpeed;

	if(FdVitality <= 0 )
		return FALSE;

	return TRUE;
}

//----------------------------------------------
void TbulHoming::Render( void )
{
	std::vector<Vector2D> vec;
	vec.push_back(FvPosition);

	// ビューポート変換
	FpGame->ViewPortTransform( vec );
	RECT srcRec =  { TRIMMING__IMAGE_LTX, TRIMMING__IMAGE_LTY, TRIMMING__IMAGE_RBX, TRIMMING__IMAGE_RBY};			
	pos = D3DXVECTOR3( (float)vec[0].x, (float)vec[0].y, 0);
	

	// 弾の後ろにぼかしを入れる
	FpGame->FpSprites->RenderEx(
							&srcRec,
							pos,																// DrawPosition
							D3DXVECTOR3((float)(FvScale.x*1.5) , (float)(FvScale.y*1.5), 1),				// Scaling
							D3DXVECTOR3(0, 0, 0),												// Rotation
							&D3DXVECTOR3 ((float)(FiImageWidth/2), (float)(FiImageHeight/2), 0),	// RotationCenter
							0.4,																// Alpha
							D3DCOLOR(1));	


	// 画像を表示する座標
	FpGame->FpSprites->RenderEx(
							&srcRec,
							pos,																// DrawPosition
							D3DXVECTOR3((float)FvScale.x , (float)FvScale.y, 1),				// Scaling
							D3DXVECTOR3(0, 0, 0),												// Rotation
							&D3DXVECTOR3 ((float)(FiImageWidth/2), (float)(FiImageHeight/2), 0),	// RotationCenter
							1.0,																// Alpha
							D3DCOLOR(1));														// ColorKey

}

//---------------------------------------------------------------------
// Cgdi描画
void TbulHoming::RenderCgdi()
{
	TBaseMovingObject::RenderCgdi();	
}

//----------------------------------------------