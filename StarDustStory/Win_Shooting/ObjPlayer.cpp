
#include "GameDef.h"
#include "ObjPlayer.h"

//----------------------------------------------
// �R���X�g���N�^
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
// �f�X�g���N�^
TobjPlayer::~TobjPlayer( void )
{
}

//---------------------------------------------------------------------
// �X�V
BOOL TobjPlayer::Update(double time_elapsed)
{
	return TRUE;
}

//---------------------------------------------------------------------
// �`��
void TobjPlayer::Render( void )
{
}

//---------------------------------------------------------------------
// Cgdi�`��
void TobjPlayer::RenderCgdi()
{
	TBaseMovingObject::RenderCgdi();
}

//---------------------------------------------------------------------