#include "GameDef.h"
#include "shBeamShot.h"
#include "GameWorld.h"

//----------------------------------------------
#define TRIMMING__IMAGE_LTX 80	// 
#define TRIMMING__IMAGE_LTY 20	// 
#define TRIMMING__IMAGE_RBX 100	// 
#define TRIMMING__IMAGE_RBY 40	// 

//----------------------------------------------
TshBeamShot::TshBeamShot( TsceneGame *game, const Vector2D &pos, const Vector2D &velocity)
	:TobjShot(
	Vector2D(pos.x,pos.y-5.0),	// position
	1.3,							// radius
	velocity,					// velocity
	50,							// max_speed
	Vec2DNormalize(velocity),	// heading
	1.,							// mass
	Vector2D(0.5, 1),			// scale
	10,							// turn_rate
	10,							// max_force
	1							// vitality
	),
	FpGame(game),
	FiImageWidth(TRIMMING__IMAGE_RBX - TRIMMING__IMAGE_LTX),
	FiImageHeight(TRIMMING__IMAGE_RBY - TRIMMING__IMAGE_LTY)
{
}

//----------------------------------------------
TshBeamShot::~TshBeamShot(void)
{
}

//----------------------------------------------
BOOL TshBeamShot::Update(double time_elapsed)
{
	//----------
	// 方向弾(飛ぶ方向は固定値)
	//----------
	FvVelocity.Normalize();
	FvVelocity *= FdMaxSpeed;

	if(FdVitality <= 0 || !Move(time_elapsed))
		return false;

	return true;
}

//----------------------------------------------
void TshBeamShot::Render( void )
{
	std::vector<Vector2D> vec;
	vec.push_back(FvPosition);

	// ビューポート変換
	FpGame->ViewPortTransform( vec );
	RECT srcRec =  { TRIMMING__IMAGE_LTX, TRIMMING__IMAGE_LTY, TRIMMING__IMAGE_RBX, TRIMMING__IMAGE_RBY};	// 画像の中から切り取る座標
	pos = D3DXVECTOR3( (float)vec[0].x, (float)vec[0].y, 0);
	
	// 弾の後ろにぼかしを入れる
	FpGame->FpSprites->RenderEx(
							&srcRec,
							pos,																	// DrawPosition
							D3DXVECTOR3((float)(FvScale.x*1.5) , (float)(FvScale.y*1.5), 1),		// Scaling
							D3DXVECTOR3(0, 0, 0),													// Rotation
							&D3DXVECTOR3 ((float)(FiImageWidth/2), (float)(FiImageHeight/2), 0),	// RotationCenter
							0.4,																	// Alpha
							D3DCOLOR(1.f));	


	// 画像を表示する座標
	FpGame->FpSprites->RenderEx(
							&srcRec,
							pos,																	// DrawPosition
							D3DXVECTOR3((float)FvScale.x , (float)FvScale.y, 1),					// Scaling
							D3DXVECTOR3(0, 0, 0),													// Rotation
							&D3DXVECTOR3 ((float)(FiImageWidth/2), (float)(FiImageHeight/2), 0),	// RotationCenter
							1.0,																	// Alpha
							D3DCOLOR(1));															// ColorKey

}

//---------------------------------------------------------------------
// Cgdi描画
void TshBeamShot::RenderCgdi()
{
	TBaseMovingObject::RenderCgdi();	
}