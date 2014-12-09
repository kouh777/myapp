

#include "GameDef.h"
//-------------------------------------------
#include "objEffect.h"
#include "effFinalBigExplosion.h"

//----------------------------------------------
#define TRIMMING__IMAGE_LTX 0	// 
#define TRIMMING__IMAGE_LTY 320	// 
#define TRIMMING__IMAGE_RBX 320	// 
#define TRIMMING__IMAGE_RBY 640	// 

#define IMAGE_WIDTH 320
#define IMAGE_HEIGHT 320

#define CELL_YOKO 2
#define CELL_TATE 4
#define CELL_NUM CELL_YOKO * CELL_TATE

//----------------------------------------------
TeffFinalBigExplosion::TeffFinalBigExplosion( TsceneGame *game, const Vector2D &pos, const Vector2D &velocity)
	:TobjEffect(
	game,
	pos,						// position
	0.5,						// radius
	velocity,					// velocity
	0.5,						// max_speed
	Vec2DNormalize(velocity),	// heading
	0.,							// mass
	Vector2D(5.0, 5.0),			// scale
	0,							// turn_rate
	1,							// max_force
	1							// vitality
	),
	FiTimer(0),
	FiAlpha(1.0),
	FiFrame(0)
{
	iImageWidth=TRIMMING__IMAGE_RBX - TRIMMING__IMAGE_LTX;
	iImageHeight=TRIMMING__IMAGE_RBY - TRIMMING__IMAGE_LTY;

	// ボス独自の爆発音を発生
	int ch = PlayDxSound( SND_SE_BOSS_DEATH );
	int bgm_vol = GetVolume(ch);
	SetVolume(ch, -300);
}

//----------------------------------------------
TeffFinalBigExplosion::~TeffFinalBigExplosion(void)
{
}

//----------------------------------------------
BOOL TeffFinalBigExplosion::Update(double time_elapsed)
{
	//----------
	// 爆風
	//----------
	const double dExplosionSpeed = 0.1;
	FiTimer += time_elapsed;
	FvScale.x += time_elapsed * dExplosionSpeed;
	FvScale.y += time_elapsed * dExplosionSpeed;
	if( FiTimer > 0.4 ){
		FiAlpha -= time_elapsed * 0.5;
		FiFrame++;
		if( FiFrame > CELL_NUM )
			FiFrame = 0;
		if( FiAlpha < 0 )
			FiAlpha = 0;
	}
	FvVelocity.Normalize();
	FvVelocity *= FdMaxSpeed;

	if(FiAlpha <= 0 || !Move(time_elapsed))
		return false;

	return true;
}

//----------------------------------------------
void TeffFinalBigExplosion::Render( void )
{
	std::vector<Vector2D> vec;
	vec.push_back(FvPosition);

	// ビューポート変換
	FpGame->ViewPortTransform( vec );
	RECT srcRec =  {  // 画像の中から切り取る座標
		IMAGE_WIDTH * FiFrame % CELL_YOKO,
		IMAGE_HEIGHT * FiFrame / CELL_YOKO,
		IMAGE_WIDTH * ( FiFrame % CELL_YOKO + 1),
		IMAGE_HEIGHT * ( FiFrame / CELL_YOKO + 1),
	};						
	pos = D3DXVECTOR3( (float)vec[0].x, (float)vec[0].y, 0);

	// 画像を表示する座標
	FpGame->FpExplosionSprite->RenderEx(
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
void TeffFinalBigExplosion::RenderCgdi()
{
	TBaseMovingObject::RenderCgdi();	
}