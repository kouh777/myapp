
#include "GameDef.h"
//-------------------------------------------
#include "objUi.h"
#include "uiPlayerLife.h"
#include "sceneGame.h"
#include "objPlayer.h"

//----------------------------------------------
#define TRIMMING__IMAGE_LTX 9	// 
#define TRIMMING__IMAGE_LTY 9	// 
#define TRIMMING__IMAGE_RBX 51	// 
#define TRIMMING__IMAGE_RBY 51	// 

//----------------------------------------------
TuiPlayerLife::TuiPlayerLife( TsceneGame *game, const Vector2D &pos, const Vector2D &velocity)
	:TobjUi(
	game,
	pos,						// position
	0,							// radius
	velocity,					// velocity
	0,							// max_speed
	Vec2DNormalize(velocity),	// heading
	0.,							// mass
	Vector2D(1.0, 1.0),			// scale
	0,							// turn_rate
	1,							// max_force
	1							// vitality
	),
	FiTimer(0),
	FiAlpha(1.0)
{
	iImageWidth=TRIMMING__IMAGE_RBX - TRIMMING__IMAGE_LTX;
	iImageHeight=TRIMMING__IMAGE_RBY - TRIMMING__IMAGE_LTY;
}

//----------------------------------------------
TuiPlayerLife::~TuiPlayerLife(void)
{
}

//----------------------------------------------
BOOL TuiPlayerLife::Update(double time_elapsed)
{
	FvVelocity.Normalize();
	FvVelocity *= FdMaxSpeed;

	if(FiAlpha <= 0 || !Move(time_elapsed))
		return false;

	return true;
}

//----------------------------------------------
void TuiPlayerLife::Render( void )
{
	std::vector<Vector2D> vec;
	Vector2D _2d_pos;
	// プレイヤーの残機
	RECT LifeRec =  { TRIMMING__IMAGE_LTX, TRIMMING__IMAGE_LTY, TRIMMING__IMAGE_RBX, TRIMMING__IMAGE_RBY};						// 画像の中から切り取る座標	
	
	for( DWORD i = 0; i < FpGame->iLife; ++i ){
		_2d_pos = FvPosition;
		_2d_pos.x += i*20;

		vec.push_back(_2d_pos);
		// ビューポート変換
		FpGame->ViewPortTransform( UI_VIEWPORT , vec );
		pos = D3DXVECTOR3( (float)vec[0].x, (float)vec[0].y, 0);

		// プレイヤーの残機を残機数分表示する
		FpGame->FpPlayerVisorSprite->RenderEx(
							&LifeRec,
							pos,																// DrawPosition
							D3DXVECTOR3((float)FvScale.x , (float)FvScale.y, 1),				// Scaling
							D3DXVECTOR3(0, 0, 0),												// Rotation
							&D3DXVECTOR3 ((float)(FiImageWidth/2), (float)(FiImageHeight/2), 0),	// RotationCenter
							FiAlpha,																// Alpha
							D3DCOLOR(1.0f));	// ColorKey
		vec.clear();
	}
}

//---------------------------------------------------------------------
// Cgdi描画
void TuiPlayerLife::RenderCgdi()
{
	TBaseMovingObject::RenderCgdi();	
}
