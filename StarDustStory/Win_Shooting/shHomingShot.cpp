#include "GameDef.h"
#include "shHomingShot.h"
#include "GameWorld.h"

//----------------------------------------------
#define TRIMMING__IMAGE_LTX 40	// 
#define TRIMMING__IMAGE_LTY 20	// 
#define TRIMMING__IMAGE_RBX 60	// 
#define TRIMMING__IMAGE_RBY 30	//

//----------------------------------------------
TshHomingShot::TshHomingShot( TsceneGame *game, const Vector2D &pos, const Vector2D &velocity)
	:TobjShot(
	game,
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
	FiImageHeight(TRIMMING__IMAGE_RBY - TRIMMING__IMAGE_LTY),
	FpEnemy(NULL)
{
	// When this shots create, get nearset enemy.
	if(FpGame->GetNearestEnemy() != NULL)
		FpEnemy = FpGame->GetNearestEnemy();
}

//----------------------------------------------
TshHomingShot::~TshHomingShot(void)
{
}

//----------------------------------------------
BOOL TshHomingShot::Update(double time_elapsed)
{

	//----------
	// 追跡弾(弾の生成時にプレイヤーの一番近くにいた敵がいる方向を追跡する。)
	//---------
	if(FpEnemy){
		FvVelocity = FpEnemy->vPosition - FvPosition;
		// ターゲットのHPが0になったらFpEnemyにNULLを入れる
		if(FpEnemy->dVitality <= 0)
			FpEnemy = NULL;
	}
	// もし弾の速度が0になったら、FvVelocityにVector2D(0,1)を代入する
	if(FvVelocity.isZero())
		FvVelocity = Vector2D(0,1);

	FvVelocity.Normalize();
	FvVelocity *= FdMaxSpeed;

	if(FdVitality <= 0 || !Move(time_elapsed))
		return false;

	return true;
}

//----------------------------------------------
void TshHomingShot::Render( void )
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
							pos,																	// DrawPosition
							D3DXVECTOR3((float)FvScale.x , (float)FvScale.y, 1),					// Scaling
							D3DXVECTOR3(0, 0, 0),													// Rotation
							&D3DXVECTOR3 ((float)(FiImageWidth/2), (float)(FiImageHeight/2), 0),	// RotationCenter
							1.0,																	// Alpha
							D3DCOLOR(1));															// ColorKey

}

//---------------------------------------------------------------------
// Cgdi描画
void TshHomingShot::RenderCgdi()
{
	TBaseMovingObject::RenderCgdi();	
}