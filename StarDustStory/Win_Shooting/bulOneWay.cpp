
#include "GameDef.h"
#include "bulOneWay.h"
#include "GameWorld.h"

#define TRIMMING__IMAGE_LTX 160	// 
#define TRIMMING__IMAGE_LTY 120	// 
#define TRIMMING__IMAGE_RBX 170	// 
#define TRIMMING__IMAGE_RBY 130	// 

//----------------------------------------------
TbulOneWay::TbulOneWay( const Vector2D &pos, const Vector2D &velocity)
	:TobjBullet(
	pos,						// position
	0.5,						// radius
	velocity,					// velocity
	30,							// max_speed
	Vec2DNormalize(velocity),	// heading
	0.,							// mass
	Vector2D(1., 0.5),			// scale
	0,							// turn_rate
	1,							// max_force
	1							// vitality
	),
	bulletnum(0),
	timer(0),
	shotinterval(0),
	FiImageWidth(TRIMMING__IMAGE_RBX - TRIMMING__IMAGE_LTX),
	FiImageHeight(TRIMMING__IMAGE_RBY - TRIMMING__IMAGE_LTY)
{
}

//----------------------------------------------
TbulOneWay::~TbulOneWay(void)
{
}

//----------------------------------------------
BOOL TbulOneWay::Update(double time_elapsed)
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
void TbulOneWay::Render( void )
{
	std::vector<Vector2D> vec;
	vec.push_back(FvPosition);

	// ビューポート変換
	GameWorld().ViewPortTransform( vec );
	RECT srcRec =  { TRIMMING__IMAGE_LTX, TRIMMING__IMAGE_LTY, TRIMMING__IMAGE_RBX, TRIMMING__IMAGE_RBY};						// 画像の中から切り取る座標
	pos = D3DXVECTOR3( (float)vec[0].x, (float)vec[0].y, 0);

	// 画像を表示する座標
	GameWorld().FpSprites->RenderEx(
							&srcRec,
							pos,																// DrawPosition
							D3DXVECTOR3((float)FvScale.x , (float)FvScale.y, 1),				// Scaling
							D3DXVECTOR3(0, 0, 0),												// Rotation
							&D3DXVECTOR3 ((float)(FiImageWidth/2), (float)(FiImageHeight/2), 0),	// RotationCenter
							1.0,																// Alpha
							D3DCOLOR(1));																// ColorKey
}

//---------------------------------------------------------------------
// Cgdi描画
void TbulOneWay::RenderCgdi()
{
	TBaseMovingObject::RenderCgdi();	
}

//----------------------------------------------