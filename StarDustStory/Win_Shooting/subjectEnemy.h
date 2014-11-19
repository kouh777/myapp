
#ifndef __SUBJECTENEMY_H_
#define __SUBJECTENEMY_H_

//-------------------------------------------
#include "BaseSubjectObject.h"

//-------------------------------------------
// “G
class TsubjectEnemy: public TBaseSubjectObject
{
public:
	TsubjectEnemy(
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

#endif // __SUBJECTENEMY_H_