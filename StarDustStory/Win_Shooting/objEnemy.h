
#ifndef __OBJENEMY_H_
#define __OBJENEMY_H_

//-------------------------------------------
#include "BaseMovingObject.h"

//-------------------------------------------
class TobjEnemy: public TBaseMovingObject
{
public:
	TobjEnemy(
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

#endif // __OBJENEMY_H_