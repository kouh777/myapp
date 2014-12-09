
#include "GameDef.h"
#include "BaseMovingObject.h"
#include "sceneGame.h"
#include "sceneStageSelect.h"

//---------------------------------------------------------------------
// 移動関数
BOOL TBaseMovingObject::Move( double elapsedtime )
{
	FvPosition += FvVelocity * elapsedtime;

	// 画面外に出た
	if( FvPosition.x < -55. ) return FALSE;
	if( FvPosition.x >  55. ) return FALSE;
	if( FvPosition.y < -55. ) return FALSE;
	if( FvPosition.y >  55. ) return FALSE;

	return TRUE;
}

//---------------------------------------------------------------------
// 描画関数
void TBaseMovingObject::Render( void )
{

}

//---------------------------------------------------------------------
// Cgdi描画関数
void TBaseMovingObject::RenderCgdi( void )
{
	std::vector<Vector2D> vec;
	vec.push_back( FvPosition );
	// ビューポート変換・ゲームシーン情報を受け取る必要がある
	double scale = 1.0;
	if( FpGame ){
		FpGame->ViewPortTransform( vec );
		scale = FpGame->iClientX / 100;
	}
	else if( FpStageSelect ){
		FpStageSelect->ViewPortTransform( vec );
		scale = FpStageSelect->iClientX / 100;
	}

	// 衝突判定用の円を描く
	Cgdi().BluePen();
	Cgdi().BlueBrush();
	Cgdi().Circle(vec[0], dBoundingRadius*scale);
}

//---------------------------------------------------------------------
// 衝突処理
void TBaseMovingObject::ReactHit(double){

	// 体力を減らす (ヒットしたものの攻撃力を受け取りたい)
	FdVitality -= 1;
	if( FpGame )
		FpGame->CreateEffect(EFF_HIT,FvPosition,FvVelocity);

#ifdef _DEBUG
				::OutputDebugString(TEXT("Hit!"));				
#endif

}