
#include "GameDef.h"
#include "subjectEnemy.h"

//----------------------------------------------
TsubjectEnemy::TsubjectEnemy(
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
			double   vitality) : TBaseSubjectObject( game,
													TBaseObject::enemy,
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

//----------------------------------------------
BOOL TsubjectEnemy::Update(double time_elapsed)
{
	return true;
}

//----------------------------------------------
void TsubjectEnemy::Render( void )
{

}

//---------------------------------------------------------------------
// Cgdi•`‰æ
void TsubjectEnemy::RenderCgdi()
{
	TBaseMovingObject::RenderCgdi();	
}

//----------------------------------------------