
#ifndef __TOBJBULLET_H__
#define __TOBJBULLET_H__

//-------------------------------------------
#include "BaseMovingObject.h"

//-------------------------------------------
class TobjBullet : public TBaseMovingObject
{
public:
	TobjBullet(
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

	virtual BOOL Update(double time_elapsed);
	virtual void Render( void );
	virtual void RenderCgdi( void );
};

//-------------------------------------------
#endif	// __TOBJBULLET_H__
