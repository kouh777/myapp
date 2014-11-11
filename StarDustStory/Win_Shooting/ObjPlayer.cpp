
#include "GameDef.h"
#include "ObjPlayer.h"

//----------------------------------------------
// コンストラクタ
TobjPlayer::TobjPlayer(
			TsceneGame *game,
			Vector2D position,
            double   radius,
            Vector2D velocity,
            double   max_speed,
            Vector2D heading,
            double   mass,
            Vector2D scale,
            double   turn_rate,
            double   max_force,
			double   vitality) : TBaseMovingObject(	game,
													TBaseObject::player,
													position,
													radius,
													velocity,
													max_speed,
													heading,
													mass,
													scale,
													turn_rate,
													max_force,
													vitality)
{

}

//---------------------------------------------------------------------
// デストラクタ
TobjPlayer::~TobjPlayer( void )
{
}

//---------------------------------------------------------------------
// 更新
BOOL TobjPlayer::Update(double time_elapsed)
{
	return TRUE;
}

//---------------------------------------------------------------------
// 描画
void TobjPlayer::Render( void )
{
}

//---------------------------------------------------------------------
// Cgdi描画
void TobjPlayer::RenderCgdi()
{
	TBaseMovingObject::RenderCgdi();
}

//---------------------------------------------------------------------