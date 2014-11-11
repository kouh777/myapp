
#include "GameDef.h"
#include "objBullet.h"
#include "GameWorld.h"

//----------------------------------------------
TobjBullet::TobjBullet(
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
													TBaseObject::bullet,
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
BOOL TobjBullet::Update(double time_elapsed)
{
	return true;
}

//----------------------------------------------
void TobjBullet::Render( void )
{

}

//---------------------------------------------------------------------
// Cgdi•`‰æ
void TobjBullet::RenderCgdi()
{
	TBaseMovingObject::RenderCgdi();	
}

//----------------------------------------------