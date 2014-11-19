
#include "GameDef.h"
#include "observerEnemy.h"

//----------------------------------------------
TobserverEnemy::TobserverEnemy(
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
			double   vitality) : TBaseObserverObject( game,
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
BOOL TobserverEnemy::Update(double time_elapsed)
{
	return true;
}

//----------------------------------------------
void TobserverEnemy::Render( void )
{

}

//---------------------------------------------------------------------
// Cgdi•`‰æ
void TobserverEnemy::RenderCgdi()
{
	TBaseMovingObject::RenderCgdi();	
}

//----------------------------------------------