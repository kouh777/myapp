#include "GameDef.h"
#include "shMultipleShot.h"
#include "GameWorld.h"

//----------------------------------------------
#define TRIMMING__IMAGE_LTX 40	// 
#define TRIMMING__IMAGE_LTY 20	// 
#define TRIMMING__IMAGE_RBX 60	// 
#define TRIMMING__IMAGE_RBY 30	//

//----------------------------------------------
TshMultipleShot::TshMultipleShot( const Vector2D &pos, const Vector2D &velocity)
	:TobjShot(
	Vector2D(pos.x,pos.y-2),	// position
	1.5,						// radius
	velocity,					// velocity
	10,							// max_speed
	Vec2DNormalize(velocity),	// heading
	1.,							// mass
	Vector2D(2.0, 2.0),			// scale
	10,							// turn_rate
	10,							// max_force
	1							// vitality
	),
	FdRadian(0),
	FdTheta(0),
	FiImageWidth(TRIMMING__IMAGE_RBX - TRIMMING__IMAGE_LTX),
	FiImageHeight(TRIMMING__IMAGE_RBY - TRIMMING__IMAGE_LTY),
	FiFlyingTime(0)
{
	// オブジェクト向いている方向を受け取り描画するための計算
	FdRadian = atan2(FvVelocity.y ,FvVelocity.x);
	FdTheta = (FdRadian/D3DX_PI+0.5) * 180 ;
}

//----------------------------------------------
TshMultipleShot::~TshMultipleShot(void)
{
}

//----------------------------------------------
BOOL TshMultipleShot::Update(double time_elapsed)
{
	//----------
	// 分裂弾(一定時間飛んだら複数の弾に分裂)
	//----------
	const int iMaxFlyingTime = 50;
	if(FiFlyingTime > iMaxFlyingTime){
		const int ShotNum = 4;					// 分裂個数の指定
		for(int i=0; i<ShotNum; ++i){
			const double SpreadRadian = 0.3;	// 分裂時に広がる角度(ラジアンで指定)
			// 分裂時の個数が奇数のとき
			if(ShotNum%2 == 1){
				GameWorld().CreateShot(
				6,
				FvPosition,
				Vector2D( cos(FdRadian+(SpreadRadian*(i-(ShotNum>>1)))), sin(FdRadian+(SpreadRadian*(i-(ShotNum>>1))))) );
			}
			// 分裂時の個数が偶数のとき
			else{
				if(i >= ShotNum>>1){
					GameWorld().CreateShot(
					6,
					FvPosition,
					Vector2D( cos(FdRadian+(SpreadRadian*(i+1-(ShotNum>>1)))), sin(FdRadian+(SpreadRadian*(i+1-(ShotNum>>1))))) );						
				}else{
					GameWorld().CreateShot(
					6,
					FvPosition,
					Vector2D( cos(FdRadian+(SpreadRadian*(i-(ShotNum>>1)))), sin(FdRadian+(SpreadRadian*(i-(ShotNum>>1))))) );
				}
			}
		}
		return false;
	}
	FiFlyingTime++;
	FvVelocity.Normalize();
	FvVelocity *= FdMaxSpeed;	

	if(FdVitality <= 0 || !Move(time_elapsed))
		return false;

	return true;
}

//----------------------------------------------
void TshMultipleShot::Render( void )
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
							pos,																	// DrawPosition
							D3DXVECTOR3((float)FvScale.x , (float)FvScale.y, 1),					// Scaling
							D3DXVECTOR3(0, 0, FdTheta),													// Rotation
							&D3DXVECTOR3 ((float)(FiImageWidth/2), (float)(FiImageHeight/2), 0),	// RotationCenter
							1.0,																	// Alpha
							D3DCOLOR(1));															// ColorKey

}

//---------------------------------------------------------------------
// Cgdi描画
void TshMultipleShot::RenderCgdi()
{
	TBaseMovingObject::RenderCgdi();	
}