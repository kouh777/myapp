
#include "GameDef.h"
#include "objEffect.h"
#include "GameWorld.h"

//----------------------------------------------
TobjEffect::TobjEffect(
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
			double   vitality) :
								FdTheta(0),
								FdRadian(0),
								FiImageWidth(0),
								FiImageHeight(0),
								TBaseMovingObject(	game,
													TBaseObject::effect,
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
BOOL TobjEffect::Update(double time_elapsed)
{
	return true;
}

//----------------------------------------------
void TobjEffect::Render( void )
{

}

//---------------------------------------------------------------------
// Cgdi•`‰æ
void TobjEffect::RenderCgdi()
{
	TBaseMovingObject::RenderCgdi();	
}