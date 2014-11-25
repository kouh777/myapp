
#include "GameDef.h"
//-------------------------------------------
#include "objEffect.h"
#include "effScope.h"

//----------------------------------------------
#define TRIMMING__IMAGE_LTX 0	// 
#define TRIMMING__IMAGE_LTY 0	// 
#define TRIMMING__IMAGE_RBX 65	// 
#define TRIMMING__IMAGE_RBY 72	// 

//----------------------------------------------
TeffScope::TeffScope( TsceneGame *game, const Vector2D &pos, const Vector2D &velocity)
	:TobjEffect(
	game,
	pos,						// position
	0.5,						// radius
	velocity,					// velocity
	0,							// max_speed
	Vec2DNormalize(velocity),	// heading
	0.,							// mass
	Vector2D(0.5, 0.5),			// scale
	0,							// turn_rate
	1,							// max_force
	1							// vitality
	),
	FiTimer(0),
	FiAlpha(0.8),
	FbBlinkEnd(false),
	FiBlinkNum(0)
{
	iImageWidth=TRIMMING__IMAGE_RBX - TRIMMING__IMAGE_LTX;
	iImageHeight=TRIMMING__IMAGE_RBY - TRIMMING__IMAGE_LTY;
}

//----------------------------------------------
TeffScope::~TeffScope(void)
{
}

//----------------------------------------------
BOOL TeffScope::Update(double time_elapsed)
{
	//----------
	// ボス弱点表示用スコープ
	//----------
	const int MAX_BLINK_NUM = 3;	//　ブリンクの最大数
	FiTimer += time_elapsed;
	if( FiTimer > 0.4 ){
		if(FiAlpha == 0.8){ 
			FiAlpha = 0;
			FiTimer = 0;
		}else if(FiAlpha == 0){
			FiAlpha = 0.8;
			FiTimer = 0;
			FiBlinkNum++;
		}
	}
	if( FiBlinkNum > MAX_BLINK_NUM ){
		FbBlinkEnd = true;
	}
	FvVelocity.Normalize();
	FvVelocity *= FdMaxSpeed;

	if(FbBlinkEnd || !Move(time_elapsed))
		return false;

	return true;
}

//----------------------------------------------
void TeffScope::Render( void )
{
	std::vector<Vector2D> vec;
	vec.push_back(FvPosition);

	// ビューポート変換
	FpGame->ViewPortTransform( vec );
	RECT srcRec =  { TRIMMING__IMAGE_LTX, TRIMMING__IMAGE_LTY, TRIMMING__IMAGE_RBX, TRIMMING__IMAGE_RBY};						// 画像の中から切り取る座標
	pos = D3DXVECTOR3( (float)vec[0].x, (float)vec[0].y, 0);

	// 画像を表示する座標
	FpGame->FpScope->RenderEx(
							&srcRec,
							pos,																// DrawPosition
							D3DXVECTOR3((float)FvScale.x , (float)FvScale.y, 1),				// Scaling
							D3DXVECTOR3(0, 0, 0),												// Rotation
							&D3DXVECTOR3 ((float)(FiImageWidth/2), (float)(FiImageHeight/2), 0),	// RotationCenter
							FiAlpha,																// Alpha
							D3DCOLOR(1));																// ColorKey
}

//---------------------------------------------------------------------
// Cgdi描画
void TeffScope::RenderCgdi()
{
	TBaseMovingObject::RenderCgdi();	
}