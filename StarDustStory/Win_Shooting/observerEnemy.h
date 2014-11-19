
#ifndef __OBSERVERENEMY_H_
#define __OBSERVERENEMY_H_

//-------------------------------------------
#include "BaseObserverObject.h"

//-------------------------------------------
// “G
class TobserverEnemy: public TBaseObserverObject
{
public:
	TobserverEnemy(
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
			double   vitality);

	virtual BOOL Update(double time_elapsed);
	virtual void Render( void );
	virtual void RenderCgdi( void );

};

#endif // __OBSERVERENEMY_H_