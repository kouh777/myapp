
#ifndef __OBJPLAYER_H__
#define __OBJPLAYER_H__

//---------------------------------------------------------------------
#include "BaseMovingObject.h"

//---------------------------------------------------------------------
// é©ã@Å@
class TobjPlayer : public TBaseMovingObject
{
public:
	TobjPlayer(
			Vector2D position,
            double   radius,
            Vector2D velocity,
            double   max_speed,
            Vector2D heading,
            double   mass,
            Vector2D scale,
            double   turn_rate,
            double   max_force,
			double   vitality);
	virtual ~TobjPlayer( void );

	virtual BOOL Update(double time_elapsed);
	virtual void Render( void );
	virtual void RenderCgdi( void );
};

//---------------------------------------------------------------------
#endif	// __OBJPLAYER_H__