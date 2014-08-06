
#include "GameDef.h"
#include "objHomingShot.h"
#include "GameWorld.h"
#include "objEnemy.h"

//---------------------------------------------------------------------
#define TRIMMING__IMAGE_LTX 40	// 
#define TRIMMING__IMAGE_LTY 20	// 
#define TRIMMING__IMAGE_RBX 60	// 
#define TRIMMING__IMAGE_RBY 30	// 

//----------------------------------------------
TobjHomingShot::TobjHomingShot( const Vector2D &pos, 
	const Vector2D &velocity )
	:TBaseMovingObject( TBaseObject::shot, 
						Vector2D(pos.x,pos.y-2), 
						1.5, 
						velocity, 
						60., 
						Vec2DNormalize(velocity), 
						1., 
						Vector2D(2., 2.), 
						10., 
						10.0, 
						1 ),
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
TobjHomingShot::~TobjHomingShot(void)
{
}

//----------------------------------------------
BOOL TobjHomingShot::Update(double time_elapsed)
{
	if(FdVitality <= 0)
		return FALSE;
	return TRUE;
}

//----------------------------------------------
void TobjHomingShot::Render( void )
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
							pos,																// DrawPosition
							D3DXVECTOR3((float)(FvScale.x*1.5) , (float)(FvScale.y*1.5), 1),				// Scaling
							D3DXVECTOR3(0, 0, 0),												// Rotation
							&D3DXVECTOR3 ((float)(FiImageWidth/2), (float)(FiImageHeight/2), 0),	// RotationCenter
							0.4,																// Alpha
							D3DCOLOR(1.f));	


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
void TobjHomingShot::RenderCgdi()
{
	TBaseMovingObject::RenderCgdi();	
}

//----------------------------------------------