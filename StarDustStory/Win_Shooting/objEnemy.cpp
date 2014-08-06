
#include "GameDef.h"
#include "objEnemy.h"
#include "GameWorld.h"

//----------------------------------------------
TobjEnemy::TobjEnemy(
			Vector2D position,
            double   radius,
            Vector2D velocity,
            double   max_speed,
            Vector2D heading,
            double   mass,
            Vector2D scale,
            double   turn_rate,
            double   max_force,
			double   vitality) : TBaseMovingObject(	TBaseObject::enemy,
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
BOOL TobjEnemy::Update(double time_elapsed)
{
	return true;
}

//----------------------------------------------
void TobjEnemy::Render( void )
{

}

//---------------------------------------------------------------------
// Cgdi•`‰æ
void TobjEnemy::RenderCgdi()
{
	TBaseMovingObject::RenderCgdi();	
}

//----------------------------------------------