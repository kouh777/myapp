

#include "GameDef.h"
//-------------------------------------------
#include "objEffect.h"
#include "effHit.h"

//----------------------------------------------
#define TRIMMING__IMAGE_LTX 0	// 
#define TRIMMING__IMAGE_LTY 384	// 
#define TRIMMING__IMAGE_RBX 192	// 
#define TRIMMING__IMAGE_RBY	576	// 

//----------------------------------------------
TeffHit::TeffHit( TsceneGame *game, const Vector2D &pos, const Vector2D &velocity)
	:TobjEffect(
	game,
	pos,						// position
	0.5,						// radius
	velocity,					// velocity
	0.5,						// max_speed
	Vec2DNormalize(velocity),	// heading
	0.,							// mass
	Vector2D(0.08, 0.08),		// scale
	0,							// turn_rate
	1,							// max_force
	1							// vitality
	),
	FiTimer(0),
	FiAlpha(1.0)
{
	iImageWidth=TRIMMING__IMAGE_RBX - TRIMMING__IMAGE_LTX;
	iImageHeight=TRIMMING__IMAGE_RBY - TRIMMING__IMAGE_LTY;

	// ヒット時の効果音
	int ch = PlayDxSound( SND_SE_SHOT );
	int bgm_vol = GetVolume(ch);
	SetVolume(ch, -200);
}

//----------------------------------------------
TeffHit::~TeffHit(void)
{
}

//----------------------------------------------
BOOL TeffHit::Update(double time_elapsed)
{
	//----------
	// 爆風
	//----------
	const double dExplosionSpeed = 0.3;
	const double dFadeOutSpeed = 3.0;
	FiTimer += time_elapsed;
	FvScale.x += time_elapsed * dExplosionSpeed;
	FvScale.y += time_elapsed * dExplosionSpeed;
	if( FiTimer > 0.2 ){
		FiAlpha -= time_elapsed * dFadeOutSpeed;
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
void TeffHit::Render( void )
{
	std::vector<Vector2D> vec;
	vec.push_back(FvPosition);

	// ビューポート変換
	FpGame->ViewPortTransform( vec );
	RECT srcRec =  { TRIMMING__IMAGE_LTX, TRIMMING__IMAGE_LTY, TRIMMING__IMAGE_RBX, TRIMMING__IMAGE_RBY};						// 画像の中から切り取る座標
	pos = D3DXVECTOR3( (float)vec[0].x, (float)vec[0].y, 0);

	// 画像を表示する座標
	FpGame->FpHit->RenderEx(
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
void TeffHit::RenderCgdi()
{
	TBaseMovingObject::RenderCgdi();	
}