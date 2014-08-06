#include "GameDef.h"
#include "shAimingShot.h"
#include "GameWorld.h"

//----------------------------------------------
#define TRIMMING__IMAGE_LTX 40	// 
#define TRIMMING__IMAGE_LTY 20	// 
#define TRIMMING__IMAGE_RBX 60	// 
#define TRIMMING__IMAGE_RBY 30	//

//----------------------------------------------
TshAimingShot::TshAimingShot( const Vector2D &pos, const Vector2D &velocity)
	:TobjShot(
	Vector2D(pos.x,pos.y-2),	// position
	1.5,							// radius
	velocity,					// velocity
	60,							// max_speed
	Vec2DNormalize(velocity),	// heading
	1.,							// mass
	Vector2D(2.0, 2.0),			// scale
	10,							// turn_rate
	10,							// max_force
	1							// vitality
	),
	FiImageWidth(TRIMMING__IMAGE_RBX - TRIMMING__IMAGE_LTX),
	FiImageHeight(TRIMMING__IMAGE_RBY - TRIMMING__IMAGE_LTY)
{
	// When this shots create, get nearset enemy.
	const TobjEnemy *FpEnemy = NULL;
	if(GameWorld().GetNearestEnemy() != NULL)
		FpEnemy = GameWorld().GetNearestEnemy();
	if(FpEnemy)
		FvVelocity = FpEnemy->vPosition - FvPosition;
	else
		FvVelocity = Vector2D(0, -1);
	FvVelocity.Normalize();
	FvVelocity *= FdMaxSpeed;
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
	GameWorld().ViewPortTransform( vec );
	RECT srcRec =  { TRIMMING__IMAGE_LTX, TRIMMING__IMAGE_LTY, TRIMMING__IMAGE_RBX, TRIMMING__IMAGE_RBY};						// 画像の中から切り取る座標
	pos = D3DXVECTOR3( (float)vec[0].x, (float)vec[0].y, 0);

	// 弾の後ろにぼかしを入れる
	GameWorld().FpSprites->RenderEx(
							&srcRec,
							pos,																	// DrawPosition
							D3DXVECTOR3((float)(FvScale.x*1.5) , (float)(FvScale.y*1.5), 1),		// Scaling
							D3DXVECTOR3(0, 0, 0),													// Rotation
							&D3DXVECTOR3 ((float)(FiImageWidth/2), (float)(FiImageHeight/2), 0),	// RotationCenter
							0.4,																	// Alpha
							D3DCOLOR(1.f));	


	// 画像を表示する座標
	GameWorld().FpSprites->RenderEx(
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
void TshAimingShot::RenderCgdi()
{
	TBaseMovingObject::RenderCgdi();	
}