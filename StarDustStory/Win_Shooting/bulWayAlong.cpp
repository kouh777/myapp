
#include "GameDef.h"
#include "bulWayAlong.h"
#include "GameWorld.h"

#define TRIMMING__IMAGE_LTX 160	// 
#define TRIMMING__IMAGE_LTY 120	// 
#define TRIMMING__IMAGE_RBX 170	// 
#define TRIMMING__IMAGE_RBY 130	// 

//----------------------------------------------
TbulWayAlong::TbulWayAlong( TsceneGame *game, const Vector2D &pos, const Vector2D &velocity)
	:TobjBullet(
	game,
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
	FiImageWidth(TRIMMING__IMAGE_RBX - TRIMMING__IMAGE_LTX),
	FiImageHeight(TRIMMING__IMAGE_RBY - TRIMMING__IMAGE_LTY)
{
	/*
	WayPoint[0] = TWayPoint(0, 0, 10);
	WayPoint[1] = TWayPoint(100, 0, 10);
	WayPoint[2] = TWayPoint(100, 100, 10);
	WayPoint[3] = TWayPoint(100, 0, 10);
	*/
}

//----------------------------------------------
TbulWayAlong::~TbulWayAlong(void)
{
}

//----------------------------------------------
BOOL TbulWayAlong::Update(double time_elapsed)
{
	//----------
	// 経路追従弾(飛ぶ方向は設定した経路に沿う)
	//----------

	/*
	for(int i=0; i > sizeof WayPoint / sizeof WayPoint[0]; ){
		while(FvPosition != WayPoint[i]){
			FvVelocity = WayPoint[i]-WayPoint[i+1];
			FvVelocity.Normalize();
			FvVelocity *= FdMaxSpeed;
		
			if(FvPosition==WayPoint[i]){
				++i;
				break;
			}

			if(FdVitality <= 0 || !Move(time_elapsed))
				return false;
		}
	}
	*/
	
	FvVelocity.Normalize();
	FvVelocity *= FdMaxSpeed;
	
	return true;
}

//----------------------------------------------
void TbulWayAlong::Render( void )
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
							pos,																// DrawPosition
							D3DXVECTOR3((float)FvScale.x , (float)FvScale.y, 1),				// Scaling
							D3DXVECTOR3(0, 0, 0),												// Rotation
							&D3DXVECTOR3 ((float)(FiImageWidth/2), (float)(FiImageHeight/2), 0),	// RotationCenter
							1.0,																// Alpha
							D3DCOLOR(1));																// ColorKey
}

//---------------------------------------------------------------------
// Cgdi描画
void TbulWayAlong::RenderCgdi()
{
	TBaseMovingObject::RenderCgdi();	
}

//----------------------------------------------