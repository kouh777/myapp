
#include "GameDef.h"
#include "objShot.h"
#include "GameWorld.h"

//----------------------------------------------
TobjShot::TobjShot(
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
													TBaseObject::shot,
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
TobjShot::~TobjShot(void)
{
}

//----------------------------------------------
BOOL TobjShot::Update(double time_elapsed)
{
	return TRUE;
}

//----------------------------------------------
void TobjShot::Render( void )
{
}

//---------------------------------------------------------------------
// Cgdi•`‰æ
void TobjShot::RenderCgdi()
{
	TBaseMovingObject::RenderCgdi();	
}

//----------------------------------------------